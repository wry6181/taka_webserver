#pragma once

#include "core/app.h"
#include "types.h"

typedef enum job_status job_status;
enum job_status {
    JOB_QUEUED,
    JOB_PROCESSING,
    JOB_COMPLETED,
    JOB_FAILED,

    JOB_STATE_SIZE,
};

typedef struct job job;
struct job {
    u64 id;
    u64 user_id;
    s8 comfy_id;
    job_status status;
};

typedef struct job_queue job_queue;
struct job_queue {
    mem_arena* queue_arena;
    job* jobs;
    u64 capacity;
    u64 write_pos;
    u64 read_pos;
};

typedef struct server server;
struct server {
    app_config config;
    b8(*init)(server* server_inst);
    b8(*server_process_job)(server* server_inst, job_queue* queue);
    void* state;
};

job_queue* job_queue_create(mem_arena* arena, u64 capacity);
b8 job_queue_add(job_queue* queue, job* job);
job job_queue_pop(job_queue* queue);
b8 job_queue_is_empty(job_queue* queue);
b8 job_queue_is_full(job_queue* queue);
