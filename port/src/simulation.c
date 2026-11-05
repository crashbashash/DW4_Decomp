#include "dw4/simulation.h"
#include <string.h>
static void dispatch(void *user)
{
    dw4_simulation *s=user;
    if (s->services) s->services(s->user,dw4_clock_host_world(&s->clock));
    if (s->failed) return; /* A failed timed service must not advance DM. */
    if (s->scripts && dw4_scriptengine_tick(s->scripts)) s->failed=1;
}
void dw4_simulation_init(dw4_simulation *s,dw4_scriptengine *e,void *user,
                         void (*services)(void *,uint64_t))
{
    memset(s,0,sizeof(*s)); s->scripts=e;s->user=user;s->services=services;
    dw4_clock_host_init(&s->clock,s,dispatch);
}
void dw4_simulation_hold(dw4_simulation *s,unsigned reasons,uint64_t host)
{
    if (s->holds!=reasons) {
        if (!s->holds && reasons) dw4_clock_host_pause(&s->clock);
        if (s->holds && !reasons) dw4_clock_host_resume(&s->clock);
        s->last_host=host;s->credit=s->due=0;s->started=1;
    }
    s->holds=reasons;
}
uint64_t dw4_simulation_due(dw4_simulation *s,uint64_t host)
{
    if (!s->started) { s->started=1;s->last_host=host;s->due=1; }
    if (s->holds || s->failed) { s->last_host=host;s->credit=s->due=0;return 0; }
    uint64_t delta=host>=s->last_host?host-s->last_host:0;
    s->last_host=host;
    /* Split before multiplying: host uptime and long intervals cannot overflow
     * the fractional accumulator. No catch-up cap silently drops active time. */
    s->due+=(delta/1000000000)*60;
    s->credit+=(delta%1000000000)*60;
    s->due+=s->credit/1000000000;s->credit%=1000000000;
    return s->due;
}
int dw4_simulation_step(dw4_simulation *s)
{
    if (s->holds || s->failed || !s->due) return -1;
    s->due--;s->ticks++;
    dw4_clock_host_set_raw(&s->clock,(s->ticks/60)*1000000000+
                            (s->ticks%60)*1000000000/60);
    dw4_clock_host_step(&s->clock);
    if (s->clock.error) s->failed=1;
    return s->failed?-1:0;
}
