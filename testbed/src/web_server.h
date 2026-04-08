#pragma onece

#include <types.h>
#include <server_types.h>

typedef struct server_state server_state;
struct server_state {
    f32 delta_time;
};

b8 server_init(server* server_inst);

b8 server_update(server* server_inst, f32 delta_time);
