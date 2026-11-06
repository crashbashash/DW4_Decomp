/* dw4/input.h -- the host pad state and the game's own button mapping (porting P2.4 / boot-contract W2).
 *
 * The engine reads a controller through the platform seam (`igPsx2Controller` /
 * `igPsx2ControllerManager`, porting P2.1).  A host pad is filled here: the *window* layer forwards
 * raw SDL events as portable `DW4_BTN_*`/`DW4_AXIS_*` codes, and this layer applies the **game's own
 * mapping**:
 *
 *   Cross = confirm/attack   Circle = cancel/jump   Square = guard
 *   L1 = item window         R1 = MP technique      R2 = status effects   Start = status screen
 *
 * Retail menus accept both the left stick and the D-pad (measured in the title and STATUS menus); in
 * the world only the left stick moves the player and the D-pad does nothing. The host keeps that split:
 * the pad D-pad drives menus only, while keyboard arrows (a PC control, spec "Agreed control
 * requirements") drive menus and walking. Digital directions take priority over stick drift.
 *
 * Scripted input (`--input-script`) feeds the same state for a headless run, so a check can advance
 * the menu without a window and with no key press hard-wired into the sequencer.
 */
#ifndef DW4_INPUT_H
#define DW4_INPUT_H

#include <stdint.h>

/* Portable button/axis codes the window layer emits (SDL constants stay in window.c). */
enum {
    DW4_BTN_UP = 1, DW4_BTN_DOWN, DW4_BTN_LEFT, DW4_BTN_RIGHT,
    DW4_BTN_FACE_A,     /* SDL A  -> Cross  */
    DW4_BTN_FACE_B,     /* SDL B  -> Circle */
    DW4_BTN_FACE_X,     /* SDL X  -> Square */
    DW4_BTN_FACE_Y,     /* SDL Y  -> Triangle */
    DW4_BTN_L1, DW4_BTN_R1, DW4_BTN_L2, DW4_BTN_R2,
    DW4_BTN_START, DW4_BTN_SELECT,
    DW4_BTN_QUIT,       /* the window closed */
    DW4_BTN_DPAD_UP, DW4_BTN_DPAD_DOWN, DW4_BTN_DPAD_LEFT, DW4_BTN_DPAD_RIGHT, /* the pad's D-pad: menus only */
};

enum { DW4_AXIS_LX = 1, DW4_AXIS_LY, DW4_AXIS_RX, DW4_AXIS_RY };

typedef struct {
    int   cross, circle, square, triangle;
    int   l1, r1, l2, r2, start, select;
    float lx, ly;       /* left stick, -1..1; +y is up (so Down is negative) */
    int up, down, left, right; /* keyboard arrows and scripted directions: menus and walking */
    int dpad_up, dpad_down, dpad_left, dpad_right; /* the pad's D-pad: menus only, as in retail */
    int   quit;
    int focus_lost, focus_pause, disconnected, pause, resume; /* host lifecycle, outside retail pad */
} dw4_input_state;

void dw4_input_init(dw4_input_state *st);

/* The game's mapping lives here, one function per source. Digital menu directions
 * are kept separate from physical stick axes so axis events cannot erase a press. */
void dw4_input_button(dw4_input_state *st, int btn, int down);
void dw4_input_axis(dw4_input_state *st, int axis, float value);
void dw4_input_menu_axes(const dw4_input_state *st, float *x, float *y);
/* Walking demand: the left stick, or keyboard/scripted directions. The pad D-pad never walks (retail). */
void dw4_input_walk_axes(const dw4_input_state *st, float *x, float *y);
/* The held buttons in the game's pad word (0x10 up, 0x20 right, 0x40 down, 0x80 left, 1 select, 8 start, 0x100 L2, 0x200 R2, 0x400 L1, 0x800 R1,
 * 0x1000 triangle, 0x2000 circle, 0x4000 cross, 0x8000 square); keyboard and D-pad directions both set the direction bits. */
uint32_t dw4_input_digital(const dw4_input_state *st);

/* Feed a scripted pad for frame `frame`.  The spec is a comma list of `<frame>:<name>` (a press on
 * that frame only), `<frame>+<name>` (held from that frame on) or `<frame>-<last>+<name>` (held through <last>), names: cross circle square
 * triangle start select l1 r1 l2 r2 up down left right.  Resets the state each call. */
void dw4_input_script(dw4_input_state *st, const char *spec, int frame);

#endif /* DW4_INPUT_H */
