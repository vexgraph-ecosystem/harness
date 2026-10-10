#ifndef HARNESS_SPACE_MESSAGE_H
#define HARNESS_SPACE_MESSAGE_H

#include "space/support.h"

/**
 * Text is an immutable borrowed byte span, not retained provider output. Caller
 * keeps it live and immutable until all containing histories detach. No decoding
 * or arbitrary-pointer validation. authorId=0 denotes a host/human message;
 * taskId=0 denotes ordinary discussion. Host authenticates authors separately.
 */
typedef struct Message {
    uint64_t id;
    uint64_t channelId;
    uint64_t authorId;
    uint64_t taskId;
    const char *text;
    size_t length;
} Message;

Message Message_0(void);
Message Message_6(uint64_t id, uint64_t channelId, uint64_t authorId, uint64_t taskId, const char *text, size_t length);

#define Message(...) SPACE_CONSTRUCT(Message, __VA_ARGS__)
#define Message_zero() Message_0()

uint64_t Message_getId(const Message *self);
uint64_t Message_getChannelId(const Message *self);
uint64_t Message_getAuthorId(const Message *self);
uint64_t Message_getTaskId(const Message *self);
const char *Message_getText(const Message *self);
size_t Message_getLength(const Message *self);

bool Message_toString(const Message *self, char *dest, size_t cap, bool *outTruncated);
bool Message_toStringStruct(const Message *self, char *dest, size_t cap, bool *outTruncated);

#endif
