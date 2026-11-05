/* The digivolution demo stage stagML14 (NDMW 831/832), hosted by the hub runtime without a lobby world.
 * Central's closing Digi-Lab script (entry 824 chunk 61) requests it after a Digimon changed. Its original
 * Lua runs through the same file-list/stage-object/controller owners as a hub: chunk 0 selects the old and new
 * s_<species> models from COUNTER[8+player] and SYSgetPlayerDigimon, chunk 2 generates g_changebg, i_evoline,
 * g_dchange, i_evowipe and the two models, chunk 3 starts SETDEMOCAMERA "entry" and DM_EVOLV/AM_EVOLV and runs
 * the swap sequence, then requests its only exit (PLAYERPOINT I<3>, NEXTSTAGE stagML12) on the borrowed travel
 * owner. No player is generated (the pack's funcPlayerSet is empty). Boundaries: port/docs/labo-shop.md. */
#ifndef DW4_EVODEMO_H
#define DW4_EVODEMO_H
#include "dw4/mount.h"
#include "dw4/playerrecords.h"
#include "dw4/stagetravel.h"
#include "dw4/render.h"
#include "dw4/scriptengine.h"
#include "dw4/controllers.h"
typedef struct dw4_evodemo dw4_evodemo;
typedef struct {
    const dw4_playerrecords *records;   /* copied; the scene owns its snapshot */
    const dw4_be_state *state;          /* copied (COUNTER[8..11] holds each player's species before the lab) */
    uint64_t world_ns;
    dw4_stagetravel *travel;            /* borrowed: the script's STAGECTL/PLAYERPOINT requests land here */
} dw4_evodemo_source;
dw4_evodemo *dw4_evodemo_open(dw4_mount *,const dw4_evodemo_source *,char *error,size_t cap);
void dw4_evodemo_close(dw4_evodemo *);
/* One admitted tick: services, original Lua/DM, controllers, the demo camera clock. */
int dw4_evodemo_tick(dw4_evodemo *,uint64_t ns);
/* Background colour (beBkColorInfo), then the demo models: world models through the demo camera, window
 * models through their authored cameras, in layer order. Returns the number of submitted draws. */
int dw4_evodemo_draw(dw4_evodemo *,dw4_fb *);
const char *dw4_evodemo_enable_gpu(dw4_evodemo *,int w,int h);
const char *dw4_evodemo_error(const dw4_evodemo *);
dw4_playerrecords *dw4_evodemo_records(dw4_evodemo *);
const dw4_be_state *dw4_evodemo_state(const dw4_evodemo *);
const dw4_controllers *dw4_evodemo_models(const dw4_evodemo *);
const dw4_stageobjects *dw4_evodemo_objects(const dw4_evodemo *);
/* The demo's audio owner (prepared without a device; the hub hands the session device to it on publication). */
struct dw4_frontaudio;
struct dw4_frontaudio *dw4_evodemo_audio(dw4_evodemo *);
/* Diagnostics for tests: the old and new model names the script chose, the demo camera clock (ns, 0 before
 * SETDEMOCAMERA) and its length, and the SOUND requests seen so far (comma-separated). */
typedef struct {
    char old_model[32],new_model[32];
    int camera_demo;uint64_t camera_ns,camera_end;
    char sounds[256];
    int music[2];                       /* DM_EVOLV, AM_EVOLV decoded and released by PAUSEOFF */
} dw4_evodemo_info;
int dw4_evodemo_info_get(const dw4_evodemo *,dw4_evodemo_info *);
#endif
