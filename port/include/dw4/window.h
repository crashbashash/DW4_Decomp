/* dw4/window.h — the host window/present backend (porting P4.1/P4.3, task item "a host GPU/window
 * backend").
 *
 * This is the *present* half of a host renderer: it takes the framebuffer the port's rasteriser
 * produced and shows it, either in an SDL2 window or headlessly (the SDL "dummy" video driver) so
 * the same code path can run in a check.  It is deliberately separate from the rasteriser
 * (`render.c`), which is where the game's shading model lives.
 *
 * It is **not** a GS and it does not run the VU1 microcode: per `port/docs/project/README.md` §*Renderer and
 * audio* the pipeline is reimplemented, and the microcode map is the specification.  The GPU
 * implementation of the LIGHT/TRANS/CLIP/... families is the next step; this file is the window
 * seam it will present through.
 *
 * SDL2 is optional: without `DW4_ENABLE_SDL2` every entry point fails cleanly, so the default
 * `make` needs no SDL2 and `make check` can skip the window test.
 */
#ifndef DW4_WINDOW_H
#define DW4_WINDOW_H

#include "dw4/render.h"
#include "dw4/input.h"

typedef struct dw4_window dw4_window;

/* 1 when the build was compiled with SDL2, 0 otherwise. */
int dw4_window_built(void);

/* Open a window (or, with `headless`, the SDL "dummy" video driver: no window, but the full
 * texture-upload path still runs).  Returns NULL when SDL2 is not compiled in or the driver
 * cannot start. */
dw4_window *dw4_window_open(int w, int h, const char *title, int headless);

/* Upload and show one framebuffer, scaling its source size to the window.
 * Returns 0, or -1 on failure. */
int dw4_window_present(dw4_window *win, const dw4_fb *fb);

/* Present a test colour and read it back: 1 = presented pixels keep dw4_fb's R,G,B,A byte order,
 * 0 = they do not, -1 = the check could not run.  The present path's one silent hazard is the SDL
 * pixel format — a wrong one shows red as blue in the window while the PNG written from the same
 * buffer stays correct, which is exactly what happened once. */
int dw4_window_order_ok(dw4_window *win);

/* Pump events; returns 0 when the user asked to quit (never for headless).  When `in` is non-NULL
 * the window's own keyboard and SDL gamepad events are decoded into the host pad state through
 * `dw4/input.h`'s mapping -- the window forwards raw events, the mapping (which button is Cross)
 * lives in the seam, not here. */
int dw4_window_pump(dw4_window *win, dw4_input_state *in);
/* As dw4_window_pump; the controllers after the first one (up to three) feed `mates[0..2]`, the pads of co-op players 2-4 (dw4/pads.h).
 * `mates` NULL is dw4_window_pump: those controllers then stay player 1's. */
int dw4_window_pump_mates(dw4_window *win, dw4_input_state *in, dw4_input_state mates[3]);

/* The host pad button an SDL keyboard scancode maps to (0 = unmapped): Space/Enter -> Cross,
 * Esc/Backspace -> Circle, Tab -> Start, arrows -> d-pad.  Exposed so a caller that pumps events
 * itself (the movie player, the Vulkan present loop) decodes the same keys without duplicating the
 * table. */
int dw4_window_key_button(int scancode);

/* The same for a gamepad: an SDL_GameControllerButton -> DW4_BTN_*, 0 when unused (shared with the Vulkan present). */
int dw4_window_pad_button(int sdl_button);

void dw4_window_close(dw4_window *win);
/* Modal host error: 1 = Retry, 0 = Back/unavailable. No game state advances. */
int dw4_window_retry(const char *operation, const char *path);

#endif /* DW4_WINDOW_H */
