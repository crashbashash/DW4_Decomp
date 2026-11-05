#ifndef DW4_MODELFADE_H
#define DW4_MODELFADE_H
#include "eefloat.h"
#include <stdint.h>
typedef struct {ee_f32 value,step,limit;int direction,updated;int64_t clock;} dw4_modelfade;
void dw4_modelfade_start(dw4_modelfade *,int in,ee_f32 frames,ee_f32 limit,int64_t clock);
void dw4_modelfade_tick(dw4_modelfade *,int64_t clock);
#endif
