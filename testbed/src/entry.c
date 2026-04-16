#include "web_server.h"
#include <entry.h>
#include <types.h>
#include <core/arena.h>

b8 create_server(mem_arena* arena, server* server) {
    server->config.name = "TAKA Engine";
    server->config.addr = "0.0.0.0";
    server->config.port = "8888";

    server->init = server_init;
    server->server_process_job = server_process_job;

    server->state = PUSH_STRUCT_ZERO(arena, server_state);

    return TRUE;
}
