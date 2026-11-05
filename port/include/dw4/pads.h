/* dw4/pads.h -- the host pads of the co-op players 2-4 (local co-op, spec "Agreed control requirements").
 *
 * The window layers (SDL window, Vulkan window) open the first game controller SDL sees for player 1, exactly as before. This module owns the
 * next three: it opens them, routes their SDL events into one `dw4_input_state` per mate (the same game mapping as player 1, input.c), and
 * follows hot-plug. Player 1 keeps every other source (keyboard, any controller that is not a mate's). Which physical controller drives which
 * player is the order SDL enumerates them in; a device-assignment screen is not part of this module.
 */
#ifndef DW4_PADS_H
#define DW4_PADS_H

#include "dw4/input.h"

typedef struct dw4_matepads dw4_matepads;

#ifdef DW4_ENABLE_SDL2
#include <SDL.h>
/* Open up to three controllers other than `first` (player 1's pad, or NULL) as the pads of players 2-4. */
dw4_matepads *dw4_matepads_open(SDL_GameController *first);
/* Route one SDL event. Returns 1 when the event belongs to a mate pad (button, axis, device added or removed) and was applied to
 * `mates[0..2]` (players 2..4); 0 otherwise, so the caller handles it for player 1. With `mates` NULL only hot-plug is tracked and the pads' buttons stay player 1's. `first` is player 1's open controller or NULL. */
int dw4_matepads_event(dw4_matepads *m, SDL_GameController *first, const SDL_Event *e, dw4_input_state mates[3]);
/* Test seam: register an instance id as the pad of mate `index` (0..2) without a device. */
void dw4_matepads_assign(dw4_matepads *m, unsigned index, int instance_id);
#endif
void dw4_matepads_close(dw4_matepads *m);

#endif /* DW4_PADS_H */
