#ifndef DW4_SIMULATION_H
#define DW4_SIMULATION_H
#include "dw4/clockhost.h"
#include "dw4/scriptengine.h"
enum { DW4_HOLD_PAUSE=1, DW4_HOLD_FOCUS=2, DW4_HOLD_DISCONNECT=4 };
/* Host policy: exact rational 60 Hz, independent of presentation. Borrowed VM.
 * Sample world time -> message services -> DM (retail slot 8). The caller
 * then advances its model adapters (Action2 is retail slot 17). */
typedef struct {
    dw4_clock_host clock;
    dw4_scriptengine *scripts;
    uint64_t ticks, last_host, credit, due;
    unsigned holds;
    int started, failed;
    void (*services)(void *, uint64_t);
    void *user;
} dw4_simulation;
void dw4_simulation_init(dw4_simulation *, dw4_scriptengine *, void *,
                         void (*services)(void *, uint64_t));
/* Every hold transition discards partial ticks and backlog. The application
 * holds manual pause/disconnect; changing window focus does not request a hold. */
void dw4_simulation_hold(dw4_simulation *, unsigned reasons, uint64_t host_ns);
uint64_t dw4_simulation_due(dw4_simulation *, uint64_t host_ns);
int dw4_simulation_step(dw4_simulation *);
#endif
