#include "space/channel.h"

;;DEFINITION
/**
 * DEFINITION: Channel
 *
 * Channel binds one dedicated discussion destination to a server and persona.
 * It owns only relationship metadata. Flat server history is planned, not yet
 * implemented; independent field reassignment would invalidate routing identity.
 */

;;OVERVIEW
/**
 * ============================================================================
 * CLASS: Channel (space/channel.c)
 * ============================================================================
 * STRUCT FIELDS (Mirroring space/channel.h):
 * ----------------------------------------------------------------------------
 *   Channel {
 *     uint64_t id;            // discussion destination
 *     uint64_t serverId;      // owning server scope
 *     uint64_t modelUserId;   // dedicated persona
 *   }
 *
 * FUNCTION REGISTRY:
 * ----------------------------------------------------------------------------
 * Constructors:
 *   - Channel_0() / Channel_2(serverId, modelUserId)
 *   - Channel(...) / Channel_zero()
 *
 * Getters:
 *   - Channel_getId(self)
 *   - Channel_getServerId(self)
 *   - Channel_getModelUserId(self)
 *
 * Projections:
 *   - Channel_toString(self, dest, cap, outTruncated)
 *   - Channel_toStringStruct(self, dest, cap, outTruncated)
 *
 * Invalid construction returns the empty value. Null getters return zero.
 * ============================================================================
 */

;;INTENTION("relationship fields change together through construction only, per the Conflict Triage Law + Single Class Per File Law (Java Law)")

/**
 * Returns an empty channel, not an admitted discussion destination.
 */
Channel Channel_0(void) {
    return (Channel) {0};
}

/**
 * Constructs a dedicated channel using its persona's ID in the server scope.
 */
Channel Channel_2(uint64_t serverId, uint64_t modelUserId) {
    if (serverId == 0 || modelUserId == 0) {
        THROW("channel: invalid identity");
        return Channel_0();
    }
    return (Channel) {modelUserId, serverId, modelUserId};
}

/**
 * Returns the destination identity, or zero for nullptr.
 */
uint64_t Channel_getId(const Channel *self) {
    if (self == nullptr)
        return 0;
    return (*self).id;
}

/**
 * Returns the server scope; equal IDs across servers are different channels.
 */
uint64_t Channel_getServerId(const Channel *self) {
    if (self == nullptr)
        return 0;
    return (*self).serverId;
}

/**
 * Returns the dedicated persona identity, or zero for nullptr.
 */
uint64_t Channel_getModelUserId(const Channel *self) {
    if (self == nullptr)
        return 0;
    return (*self).modelUserId;
}

/**
 * Formats a concise discussion destination.
 */
bool Channel_toString(const Channel *self, char *dest, size_t cap, bool *outTruncated) {
    return self == nullptr ? Space_format(dest, cap, outTruncated, "nullptr") :
        Space_format(dest, cap, outTruncated, "channel %llu/%llu",
            (unsigned long long) (*self).serverId, (unsigned long long) (*self).id);
}

/**
 * Formats own relationship fields in declaration order.
 */
bool Channel_toStringStruct(const Channel *self, char *dest, size_t cap, bool *outTruncated) {
    return self == nullptr ? Space_format(dest, cap, outTruncated, "nullptr") :
        Space_format(dest, cap, outTruncated, "Channel{id=%llu,serverId=%llu,modelUserId=%llu}",
            (unsigned long long) (*self).id, (unsigned long long) (*self).serverId,
            (unsigned long long) (*self).modelUserId);
}
