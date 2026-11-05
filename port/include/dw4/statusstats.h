/* SUBWND STATUS UPDATE / ONPREVIEW / OFPREVIEW (3d60e0 commands 2/4/5). */
#ifndef DW4_STATUSSTATS_H
#define DW4_STATUSSTATS_H
#include "dw4/playerrecords.h"
#include "dw4/dialogue.h"
enum dw4_statusstats_op {DW4_STATS_TEXT,DW4_STATS_UNICODE,DW4_STATS_COLOR,DW4_STATS_DEFAULTCOLOR};
typedef struct {
    int op;const char *group,*font,*text;
    dw4_unicode_object unicode;float color[3];
} dw4_statusstats_command;
typedef int (*dw4_statusstats_io)(void *,const dw4_statusstats_command *);
/* DATABASE shinka GETDATABASE -> row DIGIMONNO -> NAME. Borrowed string. */
typedef const char *(*dw4_statusstats_name)(void *,int32_t);
typedef struct {
    int valid;int32_t player,value[13];
} dw4_statusstats_snapshot;
/* All strings/buffers in commands are borrowed during the call. A failed sink
 * invalidates the snapshot; the containing window must recreate its scene.
 * UPDATE validates all input fields before publishing or replacing a snapshot.
 * Preview-off restores displayed baseline stats and record HP/MP, not stat
 * records: equipment's transaction owner restores those separately. */
int dw4_statusstats_update(dw4_statusstats_snapshot *,dw4_playerrecords *,int32_t,
    dw4_statusstats_name,void *,dw4_statusstats_io,void *,char *,size_t);
int dw4_statusstats_preview(dw4_statusstats_snapshot *,dw4_playerrecords *,int32_t,
    int on,dw4_statusstats_io,void *,char *,size_t);
/* Borrowed native dependencies outlive Title01. Suitable refresh callback for
 * dw4_statusview_context; database lookup is required, never a guessed name. */
typedef struct {
    dw4_arena *arena;dw4_handle work;int owns_work;int32_t player;
    dw4_playerrecords *players;
    dw4_scriptservices *sd;dw4_dialogue *dialogue;
    dw4_statusstats_name name;void *database;
} dw4_statusstats;
/* Lazily owns Work unless bound to a borrowed stock/SUBWND Work. Close before
 * reinitializing the facade; a borrowed Work must outlive it. Both buffers are
 * typed igIntList. The diagnostic snapshot is returned by value. */
int dw4_statusstats_bind(dw4_statusstats *,dw4_handle);
void dw4_statusstats_close(dw4_statusstats *);
dw4_statusstats_snapshot dw4_statusstats_state(const dw4_statusstats *);
int dw4_statusstats_refresh(void *,int32_t,char *,size_t);
int dw4_statusstats_compare(dw4_statusstats *,int32_t,int on,char *,size_t);
/* Consume transaction staging directly; no temporary publication to the live
 * player folder. Only ONPREVIEW colors/text are emitted; staging is borrowed. */
int dw4_statusstats_compare_folder(dw4_statusstats *,dw4_property_folder *,char *,size_t);
#endif
