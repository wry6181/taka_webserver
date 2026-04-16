#include "web_server.h"
#include "server_types.h"

#include <core/logger.h>

b8 server_init(server* server_inst){
    T_DEBUG("Init works");
    return TRUE;
}

b8 server_process_job(server* server_inst, job_queue* queue){
    return TRUE;
}
