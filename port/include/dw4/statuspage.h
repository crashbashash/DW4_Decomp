/* Retail horizontal page input shared by STATUS list controllers. */
#ifndef DW4_STATUSPAGE_H
#define DW4_STATUSPAGE_H
#include <stdint.h>
/* Pad +28|+32 (horizontal edges/repeats), +36 (analog state), and
 * +72|+76 (digital edges/repeats); sampled once per menu update. */
typedef struct {uint32_t horizontal,analog,digital;} dw4_statuspage_input;
typedef int (*dw4_statuspage_io)(void *,const char *model,const char *sequence);
/* 40dbf0/40dd30: returns 1 for a page change, 0 otherwise, -1 on failure. */
int dw4_statuspage_turn(int32_t *page,int pages,int next,const dw4_statuspage_input *,dw4_statuspage_io,void *);
#endif
