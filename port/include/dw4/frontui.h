/* dw4/frontui.h — the front-end title's own UI tree (findings #632/#633/#634/#635).
 *
 * The title/menu screen's 2D layer — the DIGIMON 4 logo, the copyright block and the menu rows —
 * is not drawn by hand: it is the pack's own scene graphs carried in `AREA.AFS` entry 620,
 *
 *     j_startlogo   -> igTransform `rogo`  -> igGeometry polySurfaceShape2, texture logo.png
 *                      igTransform `kenri` -> igGeometry polySurfaceShape4, texture mojips.png
 *     j_startmenu01 -> the single `start` line = the "Press START button" text (mojips.png v 0.758..0.984)
 *     j_startmenu02 -> the `menu`/`null1` rows = "Game Start" / "Option" (mojips.png v 0.62..0.78)
 *
 * **The title has two states (finding #605/#639).**  The game opens on the *press-start* screen —
 * the logo, the copyright and the `j_startmenu01` "Press START button" line, with no menu rows — and
 * only shows the `j_startmenu02` Game Start/Option rows once the player presses START.  The two menu
 * graphs are therefore mutually exclusive: `dw4_frontui_start` advances press-start -> menu.
 *
 * each node's drawable geometry resolved exactly (node -> mesh) and its texture resolved through the
 * pack's own material chain (`igAttrSet._attributes` -> `igTextureBindAttr._texture` ->
 * `igTextureAttr._image`).  The engine places the front-end's UI head-on in screen space: one model
 * unit is one framebuffer pixel at 640x448, +y up, origin at the centre, and the node's z orders the
 * draws (larger z is nearer, drawn last).
 *
 * **The animation is the pack's own controller data, not a frozen frame.**  Every UI node carries an
 * `igTransformSequence1_5` pop-in (finding #634) and `beNDMWTitle2` (finding #635) drives the graphs
 * with `MODELCTRL ... GENERATE <seq>` exactly like `j_startback`.  The per-graph `beAction2` OPEN
 * step carries a `beAction2JOINTSET` window and the CLOSE step a `beAction2FADESET`, so this module
 * plays the recovered schedule on the host's 60 fps tick:
 *
 *   * OPEN   j_startlogo `JOINTSET 0..30 'OS'`; j_startmenu01/02 `JOINTSET 0..15 'OS'` (one-shot);
 *            FADESET `IN` fadeTime 10 frames (logo) / 1 frame (menus);
 *   * CLOSE  FADESET `OUT` fadeTime 30 frames (logo) / 1 frame (menus);
 *   * the j_startmenu02 `select` node is the moving row indicator: LINEDW01 `JOINTSET 50..70 'OS'`
 *     (down), LINEUP00 `80..100 'OS'` (up), resting on the sequence's own `y = -60` / `-108` keys.
 *
 * A `beAction2JOINTSET` is a *time range* (frames at 60 fps -> `frames*1e9/60` ns), not a joint
 * count (findings #614/#618): a node's `_time` advances with the engine clock and is rebased onto
 * the window, clamped at `_endTime` for `OS`.  See `dw4_frontlayer.h` for the same mechanism.
 */
#ifndef DW4_FRONTUI_H
#define DW4_FRONTUI_H

#include "dw4/titlehost.h"
#include <stddef.h>
#include <stdint.h>

#include "dw4/mount.h"
#include "dw4/render.h"

typedef struct dw4_frontui dw4_frontui;

/* The title screen's two states (finding #605/#639).  The game boots into PRESS_START (the logo, the
 * copyright and the "Press START button" line); pressing START advances to MENU (the Game Start /
 * Option rows).  The two menu graphs are mutually exclusive. */
#define DW4_FRONTUI_PRESS_START 0
#define DW4_FRONTUI_MENU        1

/* Load `AREA.AFS` entry 620 and resolve its title UI graphs and inline textures.  NULL when the
 * archive or the graphs are unavailable. */
dw4_frontui *dw4_frontui_open(const dw4_mount *mnt);
/* Original boot model, from a graph or named subtree; same UI material renderer. */
dw4_frontui *dw4_frontui_open_card(const dw4_mount *, int part, int entry, const char *model);
void dw4_frontui_card_sample(dw4_frontui *, int joint_frame, int alpha);
/* Opt into ordered GPU replay; NULL reports unavailable/failed GPU. */
struct dw4_gl_layer;
const char *dw4_frontui_enable_gpu(dw4_frontui *, int w, int h);
/* Draw through an existing renderer (shared with the engine's frame) instead of opening a private one. */
const char *dw4_frontui_use_gpu(dw4_frontui *, struct dw4_gl_layer *);
int dw4_frontui_clear(dw4_frontui *,dw4_fb *,uint8_t,uint8_t,uint8_t);
const char *dw4_frontui_gpu_info(const dw4_frontui *);
void dw4_frontui_close(dw4_frontui *ui);

/* Bind the recovered controller; model visibility, joint time and fades then come
 * from its native backend. NULL restores the standalone asset-preview behavior. */
void dw4_frontui_bind_title(dw4_frontui *, const dw4_title_host *);

/* The current title state: `DW4_FRONTUI_PRESS_START` or `DW4_FRONTUI_MENU`. */
int dw4_frontui_state(const dw4_frontui *ui);

/* Advance from the press-start screen to the menu (the game's START).  No-op once in the menu; the
 * Game Start / Option rows then play their own recovered OPEN from `engine_ns`. */
void dw4_frontui_start(dw4_frontui *ui, long long engine_ns);

/* Deterministic: how many draw items the *current* state shows (press-start vs menu). */
int dw4_frontui_visible(const dw4_frontui *ui);

/* Advance the recovered controller to `engine_ns` (nanoseconds; the host feeds one 60 fps tick per
 * frame): drives the OPEN pop-in/fade from the pack's `beAction2` windows and any row-selection
 * transition.  Call before `dw4_frontui_draw`. */
void dw4_frontui_set_engine(dw4_frontui *ui, long long engine_ns);

/* Begin the pack's CLOSE step (its `beAction2FADESET OUT`): the UI fades over the recovered fade
 * time.  `dw4_frontui_alpha` reports the fade; `dw4_frontui_closing` is true until it finishes. */
void dw4_frontui_begin_close(dw4_frontui *ui, long long engine_ns);
int  dw4_frontui_closing(const dw4_frontui *ui);
int  dw4_frontui_alpha(const dw4_frontui *ui);

/* Draw the recovered UI over `fb` in the pack's screen space.  `selected` (0-based) names the
 * emphasised row; a change from the previous call plays the recovered row-selection transition
 * (the pack's own `select` indicator node).  Pass -1 to leave the previous selection.  Returns the
 * number of triangles drawn. */
int dw4_frontui_draw(dw4_frontui *ui, dw4_fb *fb, int selected);
/* Borrowed ordered submissions for diagnostics; observation does not advance clocks. */
void dw4_frontui_observe_draws(dw4_frontui *,void (*)(void *,const dw4_ui_draw *,size_t),void *);

/* Deterministic: the number of resolved draw items and the number of distinct inline textures the
 * graphs use (resolved eagerly at open, so this is the real count, not a lazy-load zero). */
int dw4_frontui_items(const dw4_frontui *ui);
int dw4_frontui_textures(const dw4_frontui *ui);

/* Deterministic: the i-th distinct resolved texture's name (e.g. "logo.png"), or NULL. */
const char *dw4_frontui_texture_at(const dw4_frontui *ui, int i);

/* Deterministic: the `rogo` logo quad's on-screen rectangle at the framebuffer's own size, in
 * pixels {x0,y0,x1,y1}.  Returns 0, or -1 when the logo node is missing. */
int dw4_frontui_logo_rect(const dw4_frontui *ui, const dw4_fb *fb, float rect[4]);

/* Deterministic: the resolved texture name of the logo item (e.g. "logo.png"), or NULL. */
const char *dw4_frontui_logo_texture(const dw4_frontui *ui);

/* Original localized stage card and recovered loading-node clock. Bare stage id. */
dw4_frontui *dw4_frontui_open_loading(const dw4_mount *, const char *stage);
void dw4_frontui_loading_sample(dw4_frontui *, uint64_t clock_ns);
int dw4_frontui_loading_ready(dw4_frontui *);
void dw4_frontui_loading_lock(dw4_frontui *);

#endif /* DW4_FRONTUI_H */
