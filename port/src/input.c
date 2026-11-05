/* dw4/input.c -- the host pad state and the game's own mapping; see include/dw4/input.h. */
#include "dw4/input.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dw4_input_init(dw4_input_state *st)
{
    memset(st, 0, sizeof(*st));
}

void dw4_input_axis(dw4_input_state *st, int axis, float value)
{
    switch (axis) {
    case DW4_AXIS_LX: st->lx = value; break;
    case DW4_AXIS_LY: st->ly = value; break;
    default: break;                     /* right stick unused by the front-end */
    }
}

void dw4_input_button(dw4_input_state *st, int btn, int down)
{
    switch (btn) {
    /* the game's face mapping: A=Cross (confirm/attack), B=Circle (cancel/jump),
     * X=Square (guard), Y=Triangle */
    case DW4_BTN_FACE_A:  st->cross = down; break;
    case DW4_BTN_FACE_B:  st->circle = down; break;
    case DW4_BTN_FACE_X:  st->square = down; break;
    case DW4_BTN_FACE_Y:  st->triangle = down; break;
    case DW4_BTN_L1:      st->l1 = down; break;
    case DW4_BTN_R1:      st->r1 = down; break;
    case DW4_BTN_L2:      st->l2 = down; break;
    case DW4_BTN_R2:      st->r2 = down; break;
    case DW4_BTN_START:   st->start = down; break;
    case DW4_BTN_SELECT:  st->select = down; break;
    case DW4_BTN_UP:      st->up = !!down; break;
    case DW4_BTN_DOWN:    st->down = !!down; break;
    case DW4_BTN_LEFT:    st->left = !!down; break;
    case DW4_BTN_RIGHT:   st->right = !!down; break;
    case DW4_BTN_DPAD_UP:    st->dpad_up = !!down; break;
    case DW4_BTN_DPAD_DOWN:  st->dpad_down = !!down; break;
    case DW4_BTN_DPAD_LEFT:  st->dpad_left = !!down; break;
    case DW4_BTN_DPAD_RIGHT: st->dpad_right = !!down; break;
    case DW4_BTN_QUIT:    st->quit = down; break;
    default: break;
    }
}

void dw4_input_menu_axes(const dw4_input_state *st, float *x, float *y)
{
    const int up = st->up || st->dpad_up, down = st->down || st->dpad_down;
    const int left = st->left || st->dpad_left, right = st->right || st->dpad_right;
    if (up || down || left || right) {
        *x = (float)(right - left);
        *y = (float)(up - down);
    } else {
        *x = st->lx;
        *y = st->ly;
    }
}

void dw4_input_walk_axes(const dw4_input_state *st, float *x, float *y)
{
    if (st->up || st->down || st->left || st->right) {
        *x = (float)(st->right - st->left);
        *y = (float)(st->up - st->down);
    } else {
        *x = st->lx;
        *y = st->ly;
    }
}

uint32_t dw4_input_digital(const dw4_input_state *in)
{
    return ((in->up || in->dpad_up) ? 0x10u : 0) | ((in->right || in->dpad_right) ? 0x20u : 0) |
           ((in->down || in->dpad_down) ? 0x40u : 0) | ((in->left || in->dpad_left) ? 0x80u : 0) |
           (in->select ? 1u : 0) | (in->start ? 8u : 0) | (in->l2 ? 0x100u : 0) | (in->r2 ? 0x200u : 0) |
           (in->l1 ? 0x400u : 0) | (in->r1 ? 0x800u : 0) | (in->triangle ? 0x1000u : 0) | (in->circle ? 0x2000u : 0) |
           (in->cross ? 0x4000u : 0) | (in->square ? 0x8000u : 0);
}

/* --- scripted input ---------------------------------------------------------------------------- */

static int name_to_btn(const char *s)
{
    if (!strcmp(s, "cross")) return DW4_BTN_FACE_A;
    if (!strcmp(s, "circle")) return DW4_BTN_FACE_B;
    if (!strcmp(s, "square")) return DW4_BTN_FACE_X;
    if (!strcmp(s, "triangle")) return DW4_BTN_FACE_Y;
    if (!strcmp(s, "start")) return DW4_BTN_START;
    if (!strcmp(s, "select")) return DW4_BTN_SELECT;
    if (!strcmp(s, "l1")) return DW4_BTN_L1;
    if (!strcmp(s, "r1")) return DW4_BTN_R1;
    if (!strcmp(s, "l2")) return DW4_BTN_L2;
    if (!strcmp(s, "r2")) return DW4_BTN_R2;
    if (!strcmp(s, "up")) return DW4_BTN_UP;
    if (!strcmp(s, "down")) return DW4_BTN_DOWN;
    if (!strcmp(s, "left")) return DW4_BTN_LEFT;
    if (!strcmp(s, "right")) return DW4_BTN_RIGHT;
    if (!strcmp(s, "quit")) return DW4_BTN_QUIT;
    return 0;
}

/* "<frame>:<name>" presses on that frame only; "<frame>+<name>" holds from that frame on; "<frame>-<last>+<name>" holds
 * through frame <last> and then releases. */
void dw4_input_script(dw4_input_state *st, const char *spec, int frame)
{
    const char *p = spec;

    if (!st)
        return;
    /* keep quit sticky across frames, clear the rest */
    {
        int quit = st->quit;
        dw4_input_init(st);
        st->quit = quit;
    }
    if (!spec)
        return;
    while (*p) {
        char *end;
        long f = strtol(p, &end, 10), last = -1;
        int hold = 0;
        int btn;
        char name[24];
        size_t n = 0;
        if (end == p)
            break;
        p = end;
        if (*p == '-') {
            last = strtol(p + 1, &end, 10);
            if (end == p + 1) break;
            p = end;
        }
        while (*p == ' ') p++;
        if (*p == ':') { hold = 0; p++; }
        else if (*p == '+') { hold = 1; p++; }
        else break;
        while (*p == ' ') p++;
        while (*p && *p != ',' && *p != ' ' && n + 1 < sizeof(name)) name[n++] = *p++;
        name[n] = 0;
        btn = name_to_btn(name);
        while (*p == ' ') p++;
        if (*p == ',') p++;
        if (!btn)
            continue;
        if (hold ? (frame >= f && (last < 0 || frame <= last)) : (frame == f))
            dw4_input_button(st, btn, 1);
    }
}
