#ifndef HARNESS_SPACE_TASK_H
#define HARNESS_SPACE_TASK_H

#include "space/support.h"

/**
 * Permissions are a host-defined bitset; this core can narrow but never grant
 * execution authority. It performs NO external actions. Lifecycle derives only
 * through start/finish/cancel and server-scoped admission/delegation.
 */
#define TASK_QUEUED 1u
#define TASK_RUNNING 2u
#define TASK_DONE 3u
#define TASK_CANCELLED 4u

typedef struct Task {
    uint64_t id;
    uint64_t channelId;
    uint64_t requesterId;
    uint64_t assigneeId;
    uint64_t parentId;
    uint64_t permissions;
    uint32_t state;
} Task;

Task Task_0(void);
Task Task_5(uint64_t id, uint64_t channelId, uint64_t requesterId, uint64_t assigneeId, uint64_t permissions);

#define Task(...) SPACE_CONSTRUCT(Task, __VA_ARGS__)
#define Task_zero() Task_0()

bool Task_start(Task *self, uint64_t actorId);
bool Task_finish(Task *self, uint64_t actorId);

/**
 * Cancellation is host-only admission; the caller must enforce host authority.
 */
bool Task_cancel(Task *self);
bool Task_delegate(const Task *parent, uint64_t actorId, uint64_t id, uint64_t channelId,
                   uint64_t assigneeId, uint64_t permissions, Task *dest);

uint64_t Task_getId(const Task *self);
uint64_t Task_getChannelId(const Task *self);
uint64_t Task_getRequesterId(const Task *self);
uint64_t Task_getAssigneeId(const Task *self);
uint64_t Task_getParentId(const Task *self);
uint64_t Task_getPermissions(const Task *self);
uint32_t Task_getState(const Task *self);

bool Task_toString(const Task *self, char *dest, size_t cap, bool *outTruncated);
bool Task_toStringStruct(const Task *self, char *dest, size_t cap, bool *outTruncated);

#endif
