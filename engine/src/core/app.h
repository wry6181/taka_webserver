#pragma once

#include "arena.h"
#include "types.h"

struct server;

typedef struct app_config app_config;
struct app_config {
    char* name;
    char* addr;
    char* port;
};

b8 app_create(mem_arena* arena, struct server* server_inst);
b8 app_run();
