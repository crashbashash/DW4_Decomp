#ifndef DW4_LOGOSEQ_H
#define DW4_LOGOSEQ_H
#include "modelwait.h"
enum { LOGO_OPEN=0x1310000, LOGO_CLOSE, LOGO_Action=MW_ACTION,
       LOGO_SQ_WAIT=0x1310100, LOGO_SQ_OPEN, LOGO_SQ_CLOSE, LOGO_SQ_ERAS };
/* Native dispatcher for the generated logo program only. Action2 and sequence
 * selection/removal are explicit host boundaries, not recovered engine code. */
typedef struct { int sequence,index,wait,refs,command,done,removed,error; } dw4_logo_seq;
typedef struct {
    void *user;
    void (*action)(void *,int);
    /* Optional instruction oracle. NULL uses the imported recovered C. */
    int (*invoke)(void *,int,const Dw4LoadIntf2Api *,const int32_t[4]);
} dw4_logo_hooks;
void dw4_logo_start(dw4_logo_seq *,int,const dw4_logo_hooks *);
void dw4_logo_tick(dw4_logo_seq *,int,const dw4_logo_hooks *);
#endif
