#include "space/message.h"

;;DEFINITION
/**
 * DEFINITION: Message
 *
 * Message is a routed immutable discussion event with optional task association.
 * Planned server history will copy metadata; payload bytes remain caller-owned.
 * This avoids allocator churn but requires explicit lifetime retention by host.
 */

;;OVERVIEW
/**
 * ============================================================================
 * CLASS: Message (space/message.c)
 * ============================================================================
 * STRUCT FIELDS (Mirroring space/message.h):
 * ----------------------------------------------------------------------------
 *   Message {
 *     uint64_t id;           // event identity
 *     uint64_t channelId;    // discussion route
 *     uint64_t authorId;     // sender; zero denotes host
 *     uint64_t taskId;       // thread; zero denotes ordinary discussion
 *     const char *text;      // borrowed immutable bytes
 *     size_t length;         // payload byte extent
 *   }
 *
 * FUNCTION REGISTRY:
 * ----------------------------------------------------------------------------
 * Constructors:
 *   - Message_0()
 *   - Message_6(id, channelId, authorId, taskId, text, length)
 *   - Message(...) / Message_zero()
 *
 * Getters:
 *   - Message_getId(self)
 *   - Message_getChannelId(self)
 *   - Message_getAuthorId(self)
 *   - Message_getTaskId(self)
 *   - Message_getText(self)
 *   - Message_getLength(self)
 *
 * Projections:
 *   - Message_toString(self, dest, cap, outTruncated)
 *   - Message_toStringStruct(self, dest, cap, outTruncated)
 *
 * Empty/null/oversized spans reject to zero without payload access. Getters
 * return safe defaults on nullptr. Payload retention is the caller's duty.
 * ============================================================================
 */

;;INTENTION("message metadata and payload admission are immutable snapshots; mutation requires a new event per the Conflict Triage Law + Single Class Per File Law (Java Law)")

/**
 * Returns an empty event, not an admissible server-history entry.
 */
Message Message_0(void) {
    return (Message) {0};
}

/**
 * Admits live immutable text with representable length, without copy/decoding.
 */
Message Message_6(uint64_t id, uint64_t channelId, uint64_t authorId, uint64_t taskId, const char *text, size_t length) {
    if (id == 0 || channelId == 0 || text == nullptr || length == 0 || length > PTRDIFF_MAX) {
        THROW("message: invalid input");
        return Message_0();
    }
    return (Message) {id, channelId, authorId, taskId, text, length};
}

/**
 * Returns the immutable event identity, or zero for nullptr.
 */
uint64_t Message_getId(const Message *self) {
    if (self == nullptr)
        return 0;
    return (*self).id;
}

/**
 * Returns the destination identity without following a pointer chain.
 */
uint64_t Message_getChannelId(const Message *self) {
    if (self == nullptr)
        return 0;
    return (*self).channelId;
}

/**
 * Returns the sender identity; zero is a host marker, not authentication proof.
 */
uint64_t Message_getAuthorId(const Message *self) {
    if (self == nullptr)
        return 0;
    return (*self).authorId;
}

/**
 * Returns the associated task identity without nesting history.
 */
uint64_t Message_getTaskId(const Message *self) {
    if (self == nullptr)
        return 0;
    return (*self).taskId;
}

/**
 * Returns borrowed text, valid only under the caller's retention contract.
 */
const char *Message_getText(const Message *self) {
    if (self == nullptr)
        return nullptr;
    return (*self).text;
}

/**
 * Returns the byte count, including embedded NUL bytes; nullptr yields zero.
 */
size_t Message_getLength(const Message *self) {
    if (self == nullptr)
        return 0;
    return (*self).length;
}

/**
 * Formats a summary without traversing or formatting the payload.
 */
bool Message_toString(const Message *self, char *dest, size_t cap, bool *outTruncated) {
    return self == nullptr ? Space_format(dest, cap, outTruncated, "nullptr") :
        Space_format(dest, cap, outTruncated, "message %llu (%zu bytes)",
            (unsigned long long) (*self).id, (*self).length);
}

/**
 * Formats metadata followed by escaped payload bytes. The draft length field
 * is embedded in the text label; declaration-order projection remains pending.
 */
bool Message_toStringStruct(const Message *self, char *dest, size_t cap, bool *outTruncated) {
    if (self == nullptr)
        return Space_format(dest, cap, outTruncated, "nullptr");
    if (!Space_format(dest, cap, outTruncated,
        "Message{id=%llu,channelId=%llu,authorId=%llu,taskId=%llu,text[length=%zu]=\"",
        (unsigned long long) (*self).id, (unsigned long long) (*self).channelId,
        (unsigned long long) (*self).authorId, (unsigned long long) (*self).taskId, (*self).length))
        return false;
    return Space_quote((*self).text, (*self).length, dest, cap, outTruncated);
}
