#include "platform/platform.h"
#include <xcb/xproto.h>

#if T_PLATFORM_LINUX

#include <core/logger.h>
#include <types.h>

#include <sys/time.h>

#if _POSIX_C_SOURCE >= 199309L
#include <time.h>
#else
#include <unistd.h> //usleep
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


b8 init_platform(mem_arena* arena, platform_state* plat_state, const char* app_name) {
    plat_state->internal_state = PUSH_STRUCT_ZERO(arena, internal_state);
    internal_state* state = (internal_state*)plat_state->internal_state;
    return TRUE;
}

void destroy_platform(platform_state* plat_state) {

}

void* platform_allocate(u64 size, b8 aligned) {
    return malloc(size);
}
void platform_free(void* block, b8 aligned) {
    free(block);
}
void* platform_zero_memory(void* block, u64 size) {
    return memset(block, 0, size);
}
void* platform_copy_memory(void* dest, const void* source, u64 size) {
    return memcpy(dest, source, size);
}
void* platform_set_memory(void* dest, i32 value, u64 size) {
    return memset(dest, value, size);
}

void platform_console_write(const char* message, u8 colour) {
    const char* colour_strings[] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
    printf("\033[%sm%s\033[0m\n", colour_strings[colour], message);
    fflush(stdout);
}
void platform_console_write_error(const char* message, u8 colour) {
    const char* colour_strings[] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
    printf("\033[%sm%s\033[0m\n", colour_strings[colour], message);
    fflush(stdout);
}

f64 platform_get_absolute_time() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec + now.tv_nsec * 0.000000001;
}

void platform_sleep(u64 ms) {
#if _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000 * 1000;
    nanosleep(&ts, 0);
#else
    if (ms >= 1000) {
        sleep(ms / 1000);
    }
    usleep((ms % 1000) * 1000);
#endif
}

#endif
