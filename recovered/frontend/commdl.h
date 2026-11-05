/* Behavioral recovery of 0x003e3b80..0x003e46a4. Names are descriptive
 * entry labels, not recovered C++ method names. Lower engine calls stay explicit. */
#ifndef DW4_RECOVERED_COMMDL_H
#define DW4_RECOVERED_COMMDL_H
#include "loadintf2.h"
enum { CM_MODELCTRL=0x5171f8, CM_GENERATE=0x517208,
       CM_ISSEQNAME=0x517218, CM_ISRUN=0x517228,
       CM_SCRATCH=0x0106f000 };
void cm_start(const Dw4LoadIntf2Api *, int32_t, int32_t, int32_t, int32_t, int32_t);
void cm_start_at(const Dw4LoadIntf2Api *, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
void cm_play(const Dw4LoadIntf2Api *, int32_t, int32_t, int32_t, int32_t, int32_t);
void cm_close(const Dw4LoadIntf2Api *, int32_t, int32_t, int32_t, int32_t, int32_t);
int32_t cm_is_sequence(const Dw4LoadIntf2Api *, int32_t, int32_t, int32_t, int32_t);
int32_t cm_is_running(const Dw4LoadIntf2Api *, int32_t, int32_t, int32_t);
void cm_poll(const Dw4LoadIntf2Api *, int32_t);
int32_t cm_ref_destroy(const Dw4LoadIntf2Api *, int32_t, int32_t);
/* Empty predicates remain in completion.c. CM_SCRATCH holds the positioned
 * send's copied vec3; adapters must reserve it, and compare payload not address. */
#endif
