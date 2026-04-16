#include "app.h"
#include "arena.h"
#include "platform/platform.h"
#include "types.h"
#include "logger.h"
#include "arena.h"
#include "server_types.h"

typedef struct app_state app_state;
struct app_state {
    server* server_inst;
    b8 is_running;
    b8 is_suspended;
    platform_state platform;
    f64 last_time;
};

static b8 init = FALSE;
static app_state _state;

b8 app_create(mem_arena* arena, server* server_inst) {
    if(init) {
        T_ERROR("app_create called more then once");
        return FALSE;
    }

    _state.server_inst = server_inst;

    init_logging();

    T_FATAL("A test message: %f", 3.14f);
    T_ERROR("A test message: %f", 3.14f);
    T_WARNING ("A test message: %f", 3.14f);
    T_INFO("A test message: %f", 3.14f);
    T_DEBUG("A test message: %f", 3.14f);
    T_TRACE("A test message: %f", 3.14f);

    _state.is_running = TRUE;
    _state.is_suspended = FALSE;

    if(!init_platform(arena, &_state.platform, server_inst->config.name)) {
        return FALSE;
    }

    if(!_state.server_inst->init(_state.server_inst)) {
        T_FATAL("Server failed to initalize");
        return FALSE;
    }

    init = TRUE;

    return TRUE;
}
b8 app_run(job_queue* queue) {
    while(_state.is_running) {
        job job = { .comfy_id = STR8_LIT("alma"), .id = 1, .user_id = 1};

        job_queue_add(queue, &job);

        if(!platform_pump_messages(&_state.platform)) {
            _state.is_running = FALSE;
        }

        if(!_state.is_suspended) {
            if (!_state.server_inst->server_process_job(_state.server_inst, queue)) {
                T_FATAL("Engine update failed, shutting down.");
                _state.is_running = FALSE;
                break;
            }
        }

        job_queue_pop(queue);

    }

    _state.is_running = FALSE;

    destroy_platform(&_state.platform);

    return TRUE;
}
