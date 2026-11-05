#ifndef DW4_HUDMETER_H
#define DW4_HUDMETER_H
#include <stdint.h>
/* beMeterCtrlOneData meter-mode state. Binary32 values use EE arithmetic. */
typedef struct {
    uint32_t maximum,ratio,step,target,display;
    int64_t nonzero,nonmax,time;
    int notch;
} dw4_hudmeter;
int dw4_hudmeter_init(dw4_hudmeter *,float maximum,int notch,int64_t nonzero,int64_t nonmax);
void dw4_hudmeter_percent(dw4_hudmeter *,float percent);
void dw4_hudmeter_tick(dw4_hudmeter *);
#endif
