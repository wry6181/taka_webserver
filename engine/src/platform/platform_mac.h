#pragma once

#include "platform/platform.h"

#if T_PLATFORM_MAC

#include "core/logger.h"

#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>
#include <objc/runtime.h>
#include <objc/message.h>
#include <stdlib.h>
#include <string.h>

typedef struct internal_state internal_state;
struct internal_state {
};

b8 init_platform(mem_arena* arena, platform_state* plat_state, const char* app_name) { return TRUE; }

void destroy_platform(platform_state* plat_state) { }

b8 platform_pump_messages(platform_state* plat_state) { return TRUE; }

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
    NSTimeInterval now = [[NSDate date] timeIntervalSince1970];
    return now;
}

void platform_sleep(u64 ms) {
    usleep(ms * 1000);
}

#endif
