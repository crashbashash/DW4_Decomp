/* dw4/frontchr.h -- the Game Start slot screen (character select), from the title pack's own graphs.
 *
 * Everything is `NDMW.AFS` entry 806: the four coloured slot panels (`j_chrselbase1`/`M01`), the menu
 * window `j_chrselmesswin`, and the windows the later states use.  Drawn head-on in screen space like
 * the title UI (one model unit = one pixel at 640x448, +y up, origin at the centre).
 * The same pack's BG02 graph supplies the animated grid, diamonds and glow beneath the panels.
 */
#ifndef DW4_FRONTCHR_H
#define DW4_FRONTCHR_H

#include "dw4/mount.h"
#include "dw4/fefont.h"
#include "dw4/render.h"

typedef struct dw4_frontchr dw4_frontchr;

dw4_frontchr *dw4_frontchr_open(const dw4_mount *mnt);
/* Opt into ordered GPU replay; NULL reports unavailable/failed GPU. */
const char *dw4_frontchr_enable_gpu(dw4_frontchr *, int w, int h);
struct dw4_gl_layer;
const char *dw4_frontchr_use_gpu(dw4_frontchr *, struct dw4_gl_layer *);
const char *dw4_frontchr_gpu_info(const dw4_frontchr *);
/* Accepted model/action feedback; callback ownership stays with the caller. */
void dw4_frontchr_set_sound(dw4_frontchr *, void (*)(void *, const char *, const char *), void *);
/* Read-only diagnostic observer of ordered UI submissions before rendering.
 * Draws and textures are borrowed only for the callback; clocks are not changed. */
void dw4_frontchr_observe_draws(dw4_frontchr *,void (*)(void *,const dw4_ui_draw *,size_t),void *);
void dw4_frontchr_close(dw4_frontchr *c);

/* Restart the screen's clocks (the panels assemble, the window opens). */
void dw4_frontchr_reset(dw4_frontchr *c);

/* Advance one 60 fps tick and draw the screen with the menu on row `sel` (0 Create, 1 Call).
 * Set DW4_CHR_SEQ=1 to print the layers' sequence keys when opening (a probe). */
void dw4_frontchr_draw(dw4_frontchr *c, dw4_fb *fb, int sel, const dw4_fefont *font);

/* The LoadIntf2 scene's starter choice (control state 4) drives the windows; its 3D preview (h_<species>, a skinned actor in the
 * portrait viewport) is drawn here over the scene's frame with this screen's actor renderer: one 60 Hz tick of the portrait for
 * `species` (0 Dorumon, 1 Agumon, 2 Veemon, 3 Guilmon), with the same fade on a change and no sound of its own. */
void dw4_frontchr_draw_preview(dw4_frontchr *c, dw4_fb *fb, int species);
/* Select a starter species with a fade-out / clear / fade-in portrait transition.
 * Repeating the current selection preserves its clocks; -1 returns to Create/Call. */
void dw4_frontchr_species(dw4_frontchr *c, int species);
const char *dw4_frontchr_species_name(int species);

/* Naming is kept in the screen so returning from confirmation preserves the edit. */
enum { DW4_CHR_SELECT, DW4_CHR_NAME, DW4_CHR_QUESTION, DW4_CHR_CONFIRM, DW4_CHR_CREATED };
#define DW4_CHR_NAME_MAX 8
void dw4_frontchr_begin_name(dw4_frontchr *c);
int dw4_frontchr_phase(const dw4_frontchr *c);
/* Direction steps (host supplies held-stick repeat) and button edges.
 * Returns 1 only for Start on the created card; Circle there resumes naming. */
int dw4_frontchr_name_input(dw4_frontchr *c, int horizontal, int vertical,
                           int cross, int circle, int start);
const char *dw4_frontchr_name(const dw4_frontchr *c);
/* Read-only naming state for layout/control validation. Column is 0..4. */
void dw4_frontchr_name_selection(const dw4_frontchr *,int *mode,int *first,int *column);

/* "Call Digimon": show a character loaded from a card as the created card (species and name), ready to log in. */
void dw4_frontchr_set_called(dw4_frontchr *c, int species, const char *name);

/* Commit to logging in. Input is locked while the pack's CLOSE plays:
 * JOINTSET 70..100, then 101..130 with a 30-frame fade. Draw advances it. */
void dw4_frontchr_begin_login(dw4_frontchr *c);
int dw4_frontchr_login_done(const dw4_frontchr *c);
/* Failed stage load: reopen the created card with name/species intact. */
void dw4_frontchr_cancel_login(dw4_frontchr *c);

#endif /* DW4_FRONTCHR_H */
