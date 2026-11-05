#ifndef DW4_STAGETRAVEL_H
#define DW4_STAGETRAVEL_H
#include "dw4/stageinput.h"
#include "dw4/scriptservices.h"
/* Host handoff boundary, not the complete retail stage controller. The SD queue
 * owns delays. Receivers only copy requests; never destroy a scene in Lua/DM.
 * Consume between ticks, prepare privately, publish only on success. */
typedef struct {
    dw4_stageinput *input;
    int32_t generate_pos;
    int pending;
    char destination[128];
} dw4_stagetravel;
/* STAGECTL NEXTSTAGE/PADINPUT and PLAYERPOINT SET/GETGENERATEPOS. Register the
 * same owner under both categories. No receiver owns the borrowed input. */
int dw4_stagetravel_service(void *,const char *,const dw4_script_value *,size_t,
    dw4_script_value *,char *,size_t);
/* A snapshot leaves the request intact for retry. Acknowledge only after the
 * owner has safely retained the destination or committed its publication. */
int dw4_stagetravel_pending(const dw4_stagetravel *,char *,size_t,int32_t *);
int dw4_stagetravel_restore(dw4_scriptservices *,uint64_t scope,dw4_stagetravel *,char *,size_t);
void dw4_stagetravel_ack(dw4_stagetravel *);
#endif
