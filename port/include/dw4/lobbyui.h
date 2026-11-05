/* Main Lobby's bounded first-greeting UI: disc-backed windows, portrait and fonts. */
#ifndef DW4_LOBBYUI_H
#define DW4_LOBBYUI_H
#include "dw4/fefont.h"
#include "dw4/scene.h"
#include "dw4/gl_layer.h"
#include "dw4/script.h"
#include "dw4/random.h"
#include "dw4/dialogue.h"
#include "dw4/modelctrl.h"
#include "dw4/hudmeter.h"
#include "dw4/playerhealth.h"
typedef struct dw4_lobbyui dw4_lobbyui;
dw4_lobbyui *dw4_lobbyui_open(const dw4_mount *, dw4_scene *, const uint8_t *, size_t);
void dw4_lobbyui_close(dw4_lobbyui *);
void dw4_lobbyui_dialogue(dw4_lobbyui *,dw4_dialogue *);
void dw4_lobbyui_start(dw4_lobbyui *);
/* Cross or Circle pressed edge; admission still obeys the authored window waits. */
void dw4_lobbyui_tick(dw4_lobbyui *, int advance);
int dw4_lobbyui_message(const dw4_lobbyui *); /* visible text index, or -1 during transitions */
int dw4_lobbyui_page(const dw4_lobbyui *);    /* 0..14, then 15 when final close completes */
int dw4_lobbyui_delay(const dw4_lobbyui *);
/* Commands select authored window model programs; queries/draws do not tick.
 * Until a model receives a command, queries retain the greeting adapter state. */
int dw4_lobbyui_script_service(void *,const char *,const dw4_script_value *,
    size_t,dw4_script_value *,char *,size_t);
void dw4_lobbyui_services_sample(dw4_lobbyui *,int64_t world_ns);
const char *dw4_lobbyui_services_error(const dw4_lobbyui *);
int dw4_lobbyui_services_tick(dw4_lobbyui *,int64_t world_ns);
void dw4_lobbyui_services_random(dw4_lobbyui *,dw4_random *,uint32_t *rhythm);
/* Specialized window ACTION sink; borrowed, never mutates the model owner. */
typedef void (*dw4_lobbyui_action)(void *,const char *model,const char *action);
void dw4_lobbyui_actions(dw4_lobbyui *,dw4_lobbyui_action,void *);
/* Publish the single joined player's original status panels. */
void dw4_lobbyui_restore_hud(dw4_lobbyui *, int species);
/* A hub with a party of 2-4: the five panels i_stpnl00..04 are one set per joined slot and the model view draws them; this HUD draws none. */
void dw4_lobbyui_party(dw4_lobbyui *,int party);
int dw4_lobbyui_talk_open(const dw4_lobbyui *);
void dw4_lobbyui_status(dw4_lobbyui *,int active);
int dw4_lobbyui_health(dw4_lobbyui *,int32_t level,int32_t hp,int32_t mp,int32_t max_hp,int32_t max_mp);
/* Borrowed meter state and authored node id; neither query advances it. */
const dw4_hudmeter *dw4_lobbyui_meter(const dw4_lobbyui *,unsigned,uint32_t *);
int dw4_lobbyui_health_publish(dw4_lobbyui *,const dw4_playerhealth *);
const dw4_modelctrl *dw4_lobbyui_model(const dw4_lobbyui *,unsigned);
int dw4_lobbyui_draw(dw4_lobbyui *, dw4_fb *);
/* Share the owning lobby context; failure closes it and falls back to CPU. */
int dw4_lobbyui_draw_backend(dw4_lobbyui *, dw4_fb *, dw4_gl_layer **);
/* One part of that draw: DW4_LOBBYUI_MODELS (the HUD panels and message-window models) and/or DW4_LOBBYUI_TEXT (the window and
 * label text, the original's FONT layer), so the lobby can put the window-layer models between them. */
enum {DW4_LOBBYUI_MODELS=1,DW4_LOBBYUI_TEXT=2};
int dw4_lobbyui_draw_parts(dw4_lobbyui *, dw4_fb *, dw4_gl_layer **, unsigned parts);
/* Last UI submission for comparison with retail GS vertices; borrowed until next draw. */
const dw4_ui_draw *dw4_lobbyui_draws(const dw4_lobbyui *, unsigned *);
#endif
