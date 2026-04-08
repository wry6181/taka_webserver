#include "server_types.h"
#include "core/arena.h"
#include "core/logger.h"
#include <stdatomic.h>

job_queue* job_queue_create(mem_arena* arena, u64 capacity) {
    job_queue* queue = PUSH_STRUCT_ZERO(arena, job_queue);
    queue->queue_arena = arena;
    queue->capacity = capacity;
    queue->jobs = PUSH_ARRAY_ZERO(arena, job, capacity);
    queue->read_pos = 0;
    queue->write_pos = 0;
    return queue;
}

b8 job_queue_add(job_queue* queue, job* job){
    if(job_queue_is_full(queue)) {
        T_ERROR("Job Queue is full");
        return FALSE;
    }
    u64 index = queue->write_pos % queue->capacity;
    queue->jobs[index] = *job;
    atomic_store_explicit((_Atomic u64*)&queue->write_pos, queue->write_pos + 1, memory_order_release);
    return TRUE;

}

job job_queue_pop(job_queue* queue){
    if(job_queue_is_empty(queue)) {
        T_ERROR("Job Queue is empty");
        return (job){0};
    }
    u64 index = queue->read_pos % queue->capacity;
    job result = queue->jobs[index];
    atomic_store_explicit((_Atomic u64*)&queue->read_pos, queue->read_pos + 1, memory_order_release);
    return result;
}

b8 job_queue_is_empty(job_queue* queue){
    return (queue->write_pos == queue->read_pos);
}

b8 job_queue_is_full(job_queue* queue) {
    return (queue->write_pos - queue->read_pos >= queue->capacity);
}
