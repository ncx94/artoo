
#ifndef _SYSTIME_H
#define _SYSTIME_H

#include <stdint.h>
#include <stddef.h>

#include "common.h"

struct SysTime {

    typedef void (*HeartbeatCallback)();

    /*
     * Hardware timer initialization
     */

    static void init(HeartbeatCallback hbcb = NULL);
    
    /*
     * Get the current system timer, a monotonically increasing
     * nanosecond clock.
     *
     * (The "Ticks" type is intentionally vague on units, to limit the
     * amount of code that makes assumptions about our time units, in
     * the event we need to change it in the future).
     */

    typedef int64_t Ticks;
    static Ticks now();

    /*
     * Convert common things to and from Ticks.
     *
     * These *must* be inlined - specifically in the case of hzTicks,
     * GCC generates calls to library code for division otherwise,
     * even with constant values.
     */

    static ALWAYS_INLINE Ticks sTicks(unsigned seconds) {
        return seconds * 1000000000ULL;
    }

    static ALWAYS_INLINE Ticks msTicks(unsigned milliseconds) {
        return milliseconds * 1000000ULL;
    }

    static ALWAYS_INLINE Ticks usTicks(unsigned microseconds) {
        return microseconds * 1000ULL;
    }

    static ALWAYS_INLINE Ticks nsTicks(unsigned nanoseconds) {
        return nanoseconds;
    }

    static ALWAYS_INLINE Ticks hzTicks(unsigned hz) {
        return 1000000000ULL / hz;
    }
};

#endif
