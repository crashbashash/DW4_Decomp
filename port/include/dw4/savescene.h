/* Interface-scene host for stagIS12 (the data-select / save screen): original Lua pack 810 and its stage data run
 * through the same file-list/stage-object/controller/dialogue owners as a hub, without the lobby. The native
 * controllers are beNDMWSaveCtrl (dw4/savectrl.h) and beNDMWSaveIntf (dw4/saveintf.h) over a host memory card
 * (dw4/memcard.h). Evidence and boundaries: port/docs/save-keeper.md. */
#ifndef DW4_SAVESCENE_H
#define DW4_SAVESCENE_H
#include "dw4/mount.h"
#include "dw4/playerrecords.h"
#include "dw4/stageinput.h"
#include "dw4/render.h"
#include "dw4/scriptengine.h"
#include "dw4/memcard.h"
typedef struct dw4_savescene dw4_savescene;
/* Which interface scene: stagIS12 (the save screen, SaveCtrl + SaveIntf) or stagIS13 (the load/join screen,
 * LoadCtrl2 + LoadIntf2, started by the pack's LOADCTRL2 GENERATE). */
/* stagIS11 (the card album) hosts the SUBWND CARD window tree (dw4/cardshop.h) instead of a save controller. */
typedef enum {DW4_SCENE_SAVE,DW4_SCENE_LOAD,DW4_SCENE_CARD,DW4_SCENE_TITLE} dw4_savescene_kind;
/* DW4_SCENE_TITLE: the title's Game Start slot screen -- LoadCtrl2 and LoadIntf2 for player 0 over the same pack as DW4_SCENE_LOAD:
 * the Create/Call window and Call Digimon's screens (memory-card chooser, data select, difficulty, log-in prompt). Create's species and
 * name screens stay in the character UI (frontchr). Its result is dw4_savescene_title_state. */
typedef struct {
    const dw4_playerrecords *records;   /* copied; the scene owns its snapshot */
    const dw4_be_state *state;
    uint64_t world_ns;
    dw4_memcard *card;                  /* borrowed; outlives the scene */
    dw4_savescene_kind kind;            /* DW4_SCENE_SAVE (zero) or DW4_SCENE_LOAD */
} dw4_savescene_source;
dw4_savescene *dw4_savescene_open(dw4_mount *,const dw4_savescene_source *,char *error,size_t cap);
void dw4_savescene_close(dw4_savescene *);
/* One admitted tick: services, original Lua, controllers, then SaveCtrl and SaveIntf. */
int dw4_savescene_tick(dw4_savescene *,uint64_t ns);
/* Pad words as dw4_hubruntime_input: stick direction bits (1 up, 2 right, 4 down, 8 left), held and pressed buttons. */
void dw4_savescene_input(dw4_savescene *,uint32_t analog,uint32_t held,uint32_t pressed);
int dw4_savescene_draw(dw4_savescene *,dw4_fb *);
/* Open the GLES3 layer the scene's UI draws on (required when the session mandates hardware); the renderer or NULL. */
const char *dw4_savescene_enable_gpu(dw4_savescene *,int w,int h);
const char *dw4_savescene_error(const dw4_savescene *);
/* After SaveCtrl's exit request: the next stage, its generate position (or -1), and 1; 0 while the scene runs. */
int dw4_savescene_exit(const dw4_savescene *,char *stage,size_t cap,int *generate_pos);
dw4_playerrecords *dw4_savescene_records(dw4_savescene *);
const dw4_be_state *dw4_savescene_state(const dw4_savescene *);
/* Diagnostics: SaveCtrl's phase/sub/subsub. */
void dw4_savescene_control(const dw4_savescene *,int *phase,int *sub,int *subsub);
const struct dw4_saveintf *dw4_savescene_intf(const dw4_savescene *);
/* Borrowed owners for tests and diagnostics: the scene's dialogue (visible texts), model controllers and databases. */
const struct dw4_dialogue *dw4_savescene_dialogue(const dw4_savescene *);
const struct dw4_controllers *dw4_savescene_models(const dw4_savescene *);
const struct dw4_databases *dw4_savescene_databases(const dw4_savescene *);
/* The card scene's SUBWND root state (dw4_cardshop_window_state), or -1 when no CARD window is running. */
int dw4_savescene_card_state(const dw4_savescene *,int *primary,int *main,int *sub);
/* DW4_SCENE_TITLE: 0 running, 1 the START prompt was answered (the scene still closes its windows and then reports its exit). A
 * called character has its card slot, area and difficulty row; a created one (Create: starter, name, GAMESTART) has card slot and
 * area -1, difficulty 0, and its new record is GETPLAYER 0 of dw4_savescene_records. */
int dw4_savescene_title_state(const dw4_savescene *,int *card_slot,int *area,int *difficulty);
/* Ticks the scene has run (its clock since it opened, in 60 Hz frames). */
uint64_t dw4_savescene_ticks(const dw4_savescene *);
/* Advance the scene up to `ticks` silent frames, until the interface is built and its first screen is up (the engine's hand-off
 * from the title shows no re-opening backdrop; the title kind runs until the Create/Call window takes the pad). Returns the ticks
 * used, or -1 on error. */
int dw4_savescene_warm(dw4_savescene *,uint64_t first_ns,uint64_t step_ns,int ticks);
/* Menu sounds: called with the model and the action (the sequence name without its SQ_ prefix) each time the controllers start a
 * sequence, as the title's front-end audio table (dw4_frontaudio_action) expects. */
void dw4_savescene_set_sound(dw4_savescene *,void (*)(void *,const char *model,const char *action),void *user);
/* Draw through an existing GPU layer instead of opening one (the engine's shared frame layer). */
struct dw4_gl_layer;
const char *dw4_savescene_use_gpu(dw4_savescene *,struct dw4_gl_layer *);
#endif
