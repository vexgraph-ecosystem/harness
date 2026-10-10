#ifndef HARNESS_SPACE_CHANNEL_H
#define HARNESS_SPACE_CHANNEL_H

#include "space/support.h"

/**
 * Dedicated model-channel metadata for the proposed server admission contract.
 * Channel ID equals that server's ModelUser ID; IDs are scoped by serverId.
 * Flat message history and HernessServer admission remain unimplemented.
 */
typedef struct Channel {
    uint64_t id;
    uint64_t serverId;
    uint64_t modelUserId;
} Channel;

Channel Channel_0(void);
Channel Channel_2(uint64_t serverId, uint64_t modelUserId);

#define Channel(...) SPACE_CONSTRUCT(Channel, __VA_ARGS__)
#define Channel_zero() Channel_0()

uint64_t Channel_getId(const Channel *self);
uint64_t Channel_getServerId(const Channel *self);
uint64_t Channel_getModelUserId(const Channel *self);

bool Channel_toString(const Channel *self, char *dest, size_t cap, bool *outTruncated);
bool Channel_toStringStruct(const Channel *self, char *dest, size_t cap, bool *outTruncated);

#endif
