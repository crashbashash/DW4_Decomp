/* Retail long-timer lifecycle and system-clock pump. Behavioral reference.
 * All arithmetic values are 64-bit bit patterns; raw time and external virtual
 * calls belong to the host. See docs/engine/system-clock.md for boundaries. */
#ifndef DW4_SYSTEMCLOCK_H
#define DW4_SYSTEMCLOCK_H
#include <stdint.h>
typedef struct {
    void *user;
    uint64_t (*read)(void *, uint32_t address, unsigned width);
    void (*write)(void *, uint32_t address, unsigned width, uint64_t value);
    uint64_t (*call)(void *, uint32_t address, const uint64_t args[8]);
} Dw4SystemClockApi;
/* Dispatch a recovered entry by retail address, retaining its virtual calls.
 * Unknown entries are delegated to api->call. Undefined retail return values
 * are intentionally not reproduced (the void operations return zero here). */
uint64_t dw4_clock_call(const Dw4SystemClockApi *, uint32_t entry,
                        uint64_t arg0, uint64_t arg1);
#endif
