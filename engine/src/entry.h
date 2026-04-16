#pragma once

#include "core/arena.h"
#include "core/app.h"
#include "core/logger.h"
#include "server_types.h"
#include "types.h"

extern b8 create_server(mem_arena* arena, server* out_server);

int main(void) {

    server server_inst;

    mem_arena* arena = arena_create(MByte(100));
    mem_arena* job_arena = arena_create(MByte(100));

    job_queue* job_queue = job_queue_create(job_arena, 1000);

    if(!create_server(arena, &server_inst)){
        T_ERROR("Could not ceate server");
        return -1;
    }

    if(!server_inst.init || !server_inst.server_process_job) {
        T_FATAL("The server func pointer must be defined");
        return -2;
    }

    if(!app_create(arena, &server_inst)) {
        T_INFO("Failed to create app");
        return 1;
    }

    if(!app_run(job_queue)) {
        T_INFO("Failed to run app");
        return 2;
    }



}
