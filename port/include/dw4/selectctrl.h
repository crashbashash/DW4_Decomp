/* Retail SELECTCTRL state machine (39cbf0). Inputs are sampled pad masks;
 * model completion is queried, never inferred from a host animation duration. */
#ifndef DW4_SELECTCTRL_H
#define DW4_SELECTCTRL_H
#include <stdint.h>
typedef struct {
    int active,state,sub,delay,latch,selected,count,vertical,cancel;
    float position[3];
    const uint8_t *enabled;
    char sequence[32];
} dw4_selectctrl;
typedef int (*dw4_selectctrl_io)(void *,int query,const char *key,const char *value);
/* io returns numeric query results, zero for commands, negative for errors.
 * GENERATE's position is published by the scene owner before this tick. */
int dw4_selectctrl_tick(dw4_selectctrl *,uint32_t analog,uint32_t held,
    uint32_t pressed,dw4_selectctrl_io,void *);
#endif
