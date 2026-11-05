/* dw4/pads.c -- see include/dw4/pads.h. */
#include "dw4/pads.h"
#include "dw4/window.h"
#include <stdlib.h>

#ifdef DW4_ENABLE_SDL2

struct dw4_matepads {
    SDL_GameController *pad[3];   /* NULL: nothing opened (or a test-seam id) */
    int id[3];                    /* SDL joystick instance id of each mate's pad, -1 when free */
};

static int instance_of(SDL_GameController *c)
{
    return c ? (int)SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(c)) : -1;
}

static dw4_matepads *alloc_pads(void)
{
    dw4_matepads *m = (dw4_matepads *)calloc(1, sizeof *m);
    if (m) for (unsigned i = 0; i < 3; i++) m->id[i] = -1;
    return m;
}

dw4_matepads *dw4_matepads_open(SDL_GameController *first)
{
    dw4_matepads *m = alloc_pads();
    if (!m) return NULL;
    const int n = SDL_NumJoysticks(), first_id = instance_of(first);
    unsigned k = 0;
    for (int i = 0; i < n && k < 3; i++) {
        if (!SDL_IsGameController(i) || (first && (int)SDL_JoystickGetDeviceInstanceID(i) == first_id)) continue;
        SDL_GameController *c = SDL_GameControllerOpen(i);
        if (!c) continue;
        m->pad[k] = c; m->id[k] = instance_of(c); k++;
    }
    return m;
}

void dw4_matepads_assign(dw4_matepads *m, unsigned index, int instance_id)
{
    if (m && index < 3) m->id[index] = instance_id;
}

static int slot_of(const dw4_matepads *m, int id)
{
    for (unsigned i = 0; id >= 0 && i < 3; i++) if (m->id[i] == id) return (int)i;
    return -1;
}

int dw4_matepads_event(dw4_matepads *m, SDL_GameController *first, const SDL_Event *e, dw4_input_state mates[3])
{
    if (!m || !e) return 0;
    int s;
    switch (e->type) {
    case SDL_CONTROLLERBUTTONDOWN:
    case SDL_CONTROLLERBUTTONUP:
        if (!mates) return 0;   /* without mate states the pad's buttons stay player 1's (menus, movies) */
        if ((s = slot_of(m, (int)e->cbutton.which)) < 0) return 0;
        { int b = dw4_window_pad_button(e->cbutton.button);
          if (b) dw4_input_button(&mates[s], b, e->type == SDL_CONTROLLERBUTTONDOWN); }
        return 1;
    case SDL_CONTROLLERAXISMOTION:
        if (!mates) return 0;
        if ((s = slot_of(m, (int)e->caxis.which)) < 0) return 0;
        if (e->caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) dw4_input_axis(&mates[s], DW4_AXIS_LX, e->caxis.value / 32767.0f);
        else if (e->caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) dw4_input_axis(&mates[s], DW4_AXIS_LY, -(e->caxis.value / 32767.0f));
        else if (e->caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT) dw4_input_button(&mates[s], DW4_BTN_L2, e->caxis.value > 16384);
        else if (e->caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT) dw4_input_button(&mates[s], DW4_BTN_R2, e->caxis.value > 16384);
        return 1;
    case SDL_CONTROLLERDEVICEADDED: {
        const int id = (int)SDL_JoystickGetDeviceInstanceID(e->cdevice.which);
        if (first && id == instance_of(first)) return 0;   /* player 1's own pad: the window layer has it */
        if (slot_of(m, id) >= 0) return 1;                   /* already a mate's */
        if (!first || !SDL_IsGameController(e->cdevice.which)) return 0;   /* the window layer takes the first pad before any mate */
        for (unsigned i = 0; i < 3; i++) if (m->id[i] < 0) {
            SDL_GameController *c = SDL_GameControllerOpen(e->cdevice.which);
            if (c) { m->pad[i] = c; m->id[i] = instance_of(c); }
            return 1;
        }
        return 0;
    }
    case SDL_CONTROLLERDEVICEREMOVED:
        if ((s = slot_of(m, (int)e->cdevice.which)) < 0) return 0;
        if (m->pad[s]) SDL_GameControllerClose(m->pad[s]);
        m->pad[s] = NULL; m->id[s] = -1; if (mates) dw4_input_init(&mates[s]);
        return 1;
    default:
        return 0;
    }
}

void dw4_matepads_close(dw4_matepads *m)
{
    if (!m) return;
    for (unsigned i = 0; i < 3; i++) if (m->pad[i]) SDL_GameControllerClose(m->pad[i]);
    free(m);
}

#else
void dw4_matepads_close(dw4_matepads *m) { (void)m; }
#endif
