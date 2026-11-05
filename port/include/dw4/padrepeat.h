#ifndef DW4_PADREPEAT_H
#define DW4_PADREPEAT_H
#include <stdint.h>
/* bePadData trigger/repeat state, shared algorithm for digital and sticks. */
typedef struct {uint32_t held,trigger,repeat;int32_t countdown,first,next;} dw4_padrepeat;
void dw4_padrepeat_init(dw4_padrepeat *);
void dw4_padrepeat_tick(dw4_padrepeat *,uint32_t held);
/* Polar classification from39b110; default adapter supplies native math leaves. */
uint32_t dw4_pad_directions_polar(float length,float angle,float threshold,float spread);
uint32_t dw4_pad_directions(float x,float y);
#endif
