/* STATUS scene lifecycle from manager 3d60e0/3d59b0 (mode zero). */
#ifndef DW4_STATUSSCENE_H
#define DW4_STATUSSCENE_H
#include "dw4/playerrecords.h"
enum dw4_statusscene_op {DW4_STATUSSCENE_COMMAND,DW4_STATUSSCENE_HOLD,DW4_STATUSSCENE_HEALTH};
typedef struct {
    int op;const char *category,*name,*key,*value;int32_t player,hp,mp,max_hp,max_mp;
} dw4_statusscene_command;
/* COMMAND executes the original category command; HOLD is SD world-disable,
 * not a simulation pause. HEALTH runs ADDHP 0 / ADDMP 0 publication through
 * the session's real player/HUD owner. All dependencies must be preflighted
 * before GENERATE. Failure retains the menu completion hold. */
typedef int (*dw4_statusscene_io)(void *,const dw4_statusscene_command *,char *,size_t);
typedef struct {
    dw4_playerrecords *players;dw4_statusscene_io io;void *user;
    int phase,failed;
} dw4_statusscene;
/* Initialize after preflighting the concrete factory's services/assets.
 * freeze belongs to accepted GENERATE, enter to first manager update,
 * restore to actual root completion. No calls advance simulation clocks. */
int dw4_statusscene_freeze(dw4_statusscene *,char *,size_t);
int dw4_statusscene_enter(dw4_statusscene *,char *,size_t);
int dw4_statusscene_restore(dw4_statusscene *,char *,size_t);
#endif
