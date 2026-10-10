#include "space/model_user.h"

;;DEFINITION
/**
 * DEFINITION: ModelUser
 *
 * ModelUser gives a model persona a stable server-local identity and mention
 * handle. It owns its copied name but no model execution or credential. The
 * modelId is host metadata; zero/invalid construction yields an empty value.
 */

;;OVERVIEW
/**
 * ============================================================================
 * CLASS: ModelUser (space/model_user.c)
 * ============================================================================
 * STRUCT FIELDS (Mirroring space/model_user.h):
 * ----------------------------------------------------------------------------
 *   ModelUser {
 *     uint64_t id;                          // host-assigned identity
 *     char name[MODEL_USER_NAME_CAP];       // copied mention handle
 *     uint64_t modelId;                     // selected model metadata
 *   }
 *
 * FUNCTION REGISTRY:
 * ----------------------------------------------------------------------------
 * Constructors:
 *   - ModelUser_0() / ModelUser_3(id, name, modelId)
 *   - ModelUser(...) / ModelUser_zero()
 *
 * Setters:
 *   - ModelUser_setName(self, name)
 *   - ModelUser_setModelId(self, modelId)
 *
 * Getters:
 *   - ModelUser_getId(self)
 *   - ModelUser_getName(self)
 *   - ModelUser_getModelId(self)
 *
 * Projections:
 *   - ModelUser_toString(self, dest, cap, outTruncated)
 *   - ModelUser_toStringStruct(self, dest, cap, outTruncated)
 *
 * Caller serializes mutation. Invalid setters preserve state; getters return
 * safe defaults on nullptr. Invalid construction returns the empty value.
 * ============================================================================
 */

;;INTENTION("IDs change only through construction, not setters that would corrupt server identity; per the Conflict Triage Law + Single Class Per File Law (Java Law)")

/**
 * Returns an empty identity with no registered model or handle.
 */
ModelUser ModelUser_0(void) {
    return (ModelUser) {0};
}

/**
 * Constructs a complete persona, copying the handle only after validation.
 */
ModelUser ModelUser_3(uint64_t id, const char *name, uint64_t modelId) {
    if (id == 0 || modelId == 0 || !Space_nameValid(name)) {
        THROW("model user: invalid identity");
        return ModelUser_0();
    }
    ModelUser result = {.id = id, .modelId = modelId};
    memcpy(result.name, name, strlen(name) + 1);
    return result;
}

/**
 * Rejects an invalid name without changing the copied identity.
 */
bool ModelUser_setName(ModelUser *self, const char *name) {
    if (self == nullptr || !Space_nameValid(name)) {
        THROW("model user name: invalid input");
        return false;
    }
    char copy[MODEL_USER_NAME_CAP] = {0};
    memcpy(copy, name, strlen(name) + 1);
    memcpy((*self).name, copy, sizeof(copy));
    return true;
}

/**
 * Updates model metadata; zero is never a usable model binding.
 */
bool ModelUser_setModelId(ModelUser *self, uint64_t modelId) {
    if (self == nullptr || modelId == 0) {
        THROW("model user model: invalid input");
        return false;
    }
    (*self).modelId = modelId;
    return true;
}

/**
 * Returns the persona identity, or zero for nullptr.
 */
uint64_t ModelUser_getId(const ModelUser *self) {
    if (self == nullptr)
        return 0;
    return (*self).id;
}

/**
 * Returns the borrowed mention handle, or nullptr for an absent persona.
 */
const char *ModelUser_getName(const ModelUser *self) {
    if (self == nullptr)
        return nullptr;
    return (*self).name;
}

/**
 * Returns host model metadata, not provider capabilities; nullptr yields zero.
 */
uint64_t ModelUser_getModelId(const ModelUser *self) {
    if (self == nullptr)
        return 0;
    return (*self).modelId;
}

/**
 * Formats the mention spelling; validated handles require no escaping.
 */
bool ModelUser_toString(const ModelUser *self, char *dest, size_t cap, bool *outTruncated) {
    return self == nullptr ? Space_format(dest, cap, outTruncated, "nullptr") :
        Space_format(dest, cap, outTruncated, "@%s", (*self).name);
}

/**
 * Formats own fields in declaration order without model/provider traversal.
 */
bool ModelUser_toStringStruct(const ModelUser *self, char *dest, size_t cap, bool *outTruncated) {
    return self == nullptr ? Space_format(dest, cap, outTruncated, "nullptr") :
        Space_format(dest, cap, outTruncated, "ModelUser{id=%llu,name=\"%s\",modelId=%llu}",
            (unsigned long long) (*self).id, (*self).name, (unsigned long long) (*self).modelId);
}
