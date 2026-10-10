#include "space/task.h"

;;DEFINITION
/**
 * DEFINITION: Task
 *
 * Task records explicit work ownership, thread identity, lifecycle and the host's
 * admitted permission ceiling. Delegation produces a NEW child and never mutates
 * the parent or broadens permissions. This is coordination, not tool execution.
 */

;;OVERVIEW
/**
 * ============================================================================
 * CLASS: Task (space/task.c)
 * ============================================================================
 * STRUCT FIELDS (Mirroring space/task.h):
 * ----------------------------------------------------------------------------
 *   Task {
 *     uint64_t id;            // work identity
 *     uint64_t channelId;     // discussion destination
 *     uint64_t requesterId;   // sender; zero denotes host
 *     uint64_t assigneeId;    // responsible persona
 *     uint64_t parentId;      // delegated parent; zero denotes root
 *     uint64_t permissions;   // host-admitted permission ceiling
 *     uint32_t state;         // queued/running/done/cancelled
 *   }
 *
 * FUNCTION REGISTRY:
 * ----------------------------------------------------------------------------
 * Constructors:
 *   - Task_0() / Task_5(id, channelId, requesterId, assigneeId, permissions)
 *   - Task(...) / Task_zero()
 *
 * Core Functions:
 *   - Task_start(self, actorId)
 *   - Task_finish(self, actorId)
 *   - Task_cancel(self)
 *   - Task_delegate(parent, actorId, id, channelId, assigneeId, permissions, dest)
 *
 * Getters:
 *   - Task_getId(self)
 *   - Task_getChannelId(self)
 *   - Task_getRequesterId(self)
 *   - Task_getAssigneeId(self)
 *   - Task_getParentId(self)
 *   - Task_getPermissions(self)
 *   - Task_getState(self)
 *
 * Projections:
 *   - Task_toString(self, dest, cap, outTruncated)
 *   - Task_toStringStruct(self, dest, cap, outTruncated)
 *
 * Invalid operations preserve state/output and report once. Null getters
 * return zero. Caller serializes all mutation and enforces host authority.
 * ============================================================================
 */

;;INTENTION("task fields mutate through validated lifecycle and delegation only; raw setters could forge acknowledgement/authority per the Conflict Triage Law + Single Class Per File Law (Java Law)")

/**
 * Returns an empty work identity, not a queued task.
 */
Task Task_0(void) {
    return (Task) {0};
}

/**
 * Constructs a root assignment recording a host-selected permission ceiling.
 */
Task Task_5(uint64_t id, uint64_t channelId, uint64_t requesterId, uint64_t assigneeId, uint64_t permissions) {
    if (id == 0 || channelId == 0 || assigneeId == 0) {
        THROW("task: invalid identity");
        return Task_0();
    }
    return (Task) {id, channelId, requesterId, assigneeId, 0, permissions, TASK_QUEUED};
}

/**
 * Starts a queued task only when the actor is its assigned persona.
 */
bool Task_start(Task *self, uint64_t actorId) {
    if (self == nullptr || (*self).id == 0 || actorId == 0 || actorId != (*self).assigneeId || (*self).state != TASK_QUEUED) {
        THROW("task start: rejected transition");
        return false;
    }
    (*self).state = TASK_RUNNING;
    return true;
}

/**
 * Completes running assigned work; admission alone is not completion.
 */
bool Task_finish(Task *self, uint64_t actorId) {
    if (self == nullptr || (*self).id == 0 || actorId == 0 || actorId != (*self).assigneeId || (*self).state != TASK_RUNNING) {
        THROW("task finish: rejected transition");
        return false;
    }
    (*self).state = TASK_DONE;
    return true;
}

/**
 * Records host cancellation in metadata without stopping a provider/worker.
 */
bool Task_cancel(Task *self) {
    if (self == nullptr || (*self).id == 0 || ((*self).state != TASK_QUEUED && (*self).state != TASK_RUNNING)) {
        THROW("task cancel: rejected transition");
        return false;
    }
    (*self).state = TASK_CANCELLED;
    return true;
}

/**
 * Creates a child for a running assignee with a subset of the parent's ceiling.
 * Rejection preserves both the parent and destination.
 */
bool Task_delegate(const Task *parent, uint64_t actorId, uint64_t id, uint64_t channelId,
                   uint64_t assigneeId, uint64_t permissions, Task *dest) {
    if (parent == nullptr || dest == nullptr || parent == dest || (*parent).id == 0 ||
        (*parent).state != TASK_RUNNING || actorId == 0 || actorId != (*parent).assigneeId ||
        id == 0 || id == (*parent).id || channelId == 0 || assigneeId == 0 ||
        (permissions & ~(*parent).permissions) != 0) {
        THROW("task delegate: rejected authority or identity");
        return false;
    }
    *dest = (Task) {id, channelId, actorId, assigneeId, (*parent).id, permissions, TASK_QUEUED};
    return true;
}

/**
 * Returns the work identity, or zero for nullptr.
 */
uint64_t Task_getId(const Task *self) {
    if (self == nullptr)
        return 0;
    return (*self).id;
}

/**
 * Returns the discussion destination, or zero for nullptr.
 */
uint64_t Task_getChannelId(const Task *self) {
    if (self == nullptr)
        return 0;
    return (*self).channelId;
}

/**
 * Returns the requester identity; zero denotes the trusted host marker.
 */
uint64_t Task_getRequesterId(const Task *self) {
    if (self == nullptr)
        return 0;
    return (*self).requesterId;
}

/**
 * Returns the responsible persona, or zero for nullptr.
 */
uint64_t Task_getAssigneeId(const Task *self) {
    if (self == nullptr)
        return 0;
    return (*self).assigneeId;
}

/**
 * Returns the parent thread identity, or zero for a root/absent task.
 */
uint64_t Task_getParentId(const Task *self) {
    if (self == nullptr)
        return 0;
    return (*self).parentId;
}

/**
 * Returns the inherited permission ceiling, not external execution approval.
 */
uint64_t Task_getPermissions(const Task *self) {
    if (self == nullptr)
        return 0;
    return (*self).permissions;
}

/**
 * Returns the lifecycle state; queued work must not be interpreted as done.
 */
uint32_t Task_getState(const Task *self) {
    if (self == nullptr)
        return 0;
    return (*self).state;
}

/**
 * Formats a concise work identity and lifecycle state.
 */
bool Task_toString(const Task *self, char *dest, size_t cap, bool *outTruncated) {
    return self == nullptr ? Space_format(dest, cap, outTruncated, "nullptr") :
        Space_format(dest, cap, outTruncated, "task %llu state=%u", (unsigned long long) (*self).id, (*self).state);
}

/**
 * Formats all own fields in declaration order without recursive parent access.
 */
bool Task_toStringStruct(const Task *self, char *dest, size_t cap, bool *outTruncated) {
    return self == nullptr ? Space_format(dest, cap, outTruncated, "nullptr") :
        Space_format(dest, cap, outTruncated,
            "Task{id=%llu,channelId=%llu,requesterId=%llu,assigneeId=%llu,parentId=%llu,permissions=%llu,state=%u}",
            (unsigned long long) (*self).id, (unsigned long long) (*self).channelId,
            (unsigned long long) (*self).requesterId, (unsigned long long) (*self).assigneeId,
            (unsigned long long) (*self).parentId, (unsigned long long) (*self).permissions, (*self).state);
}
