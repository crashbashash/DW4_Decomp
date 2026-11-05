#include "dw4/input.h"
#include "dw4/window.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifdef DW4_ENABLE_SDL2
#include <SDL.h>
#endif

static void axes(const dw4_input_state *in, float x, float y)
{
    float got_x, got_y;
    dw4_input_menu_axes(in, &got_x, &got_y);
    assert(got_x == x && got_y == y);
}

static void walk(const dw4_input_state *in, float x, float y)
{
    float got_x, got_y;
    dw4_input_walk_axes(in, &got_x, &got_y);
    assert(got_x == x && got_y == y);
}

int main(void)
{
    dw4_input_state in;
    dw4_input_init(&in);
    dw4_input_axis(&in, DW4_AXIS_LX, 0.75f);
    dw4_input_axis(&in, DW4_AXIS_LY, -0.6f);
    axes(&in, 0.75f, -0.6f);
    dw4_input_button(&in, DW4_BTN_UP, 1);
    axes(&in, 0, 1); /* D-pad also suppresses drift on the other axis. */
    dw4_input_axis(&in, DW4_AXIS_LY, -0.9f);
    axes(&in, 0, 1); /* Stick events cannot erase a held digital direction. */
    dw4_input_button(&in, DW4_BTN_DOWN, 1);
    axes(&in, 0, 0);
    dw4_input_button(&in, DW4_BTN_UP, 0);
    axes(&in, 0, -1); /* Releasing one opposite preserves the other. */
    dw4_input_button(&in, DW4_BTN_DOWN, 0);
    axes(&in, 0.75f, -0.9f);
    dw4_input_script(&in, "2:right,4+left", 2);
    axes(&in, 1, 0);
    dw4_input_script(&in, "2:right,4+left", 3);
    axes(&in, 0, 0);
    dw4_input_script(&in, "2:right,4+left", 20);
    axes(&in, -1, 0);
    dw4_input_script(&in, "4-6+left", 6);
    axes(&in, -1, 0);
    dw4_input_script(&in, "4-6+left", 7);
    axes(&in, 0, 0);

    /* Retail: the D-pad moves menu cursors but never the player; the stick and keyboard arrows walk. */
    dw4_input_init(&in);
    dw4_input_axis(&in, DW4_AXIS_LX, 0.5f);
    dw4_input_button(&in, DW4_BTN_DPAD_DOWN, 1);
    axes(&in, 0, -1);   /* menus follow the D-pad ... */
    walk(&in, 0.5f, 0); /* ... walking still follows only the stick */
    dw4_input_button(&in, DW4_BTN_DPAD_DOWN, 0);
    axes(&in, 0.5f, 0);
    dw4_input_button(&in, DW4_BTN_LEFT, 1);
    walk(&in, -1, 0);   /* keyboard arrows (a PC control) walk and navigate */
    axes(&in, -1, 0);
    dw4_input_button(&in, DW4_BTN_LEFT, 0);

#ifdef DW4_ENABLE_SDL2
    {
        dw4_window *win = dw4_window_open(16, 16, "input test", 1);
        const Uint8 buttons[] = {SDL_CONTROLLER_BUTTON_DPAD_UP,
            SDL_CONTROLLER_BUTTON_DPAD_DOWN, SDL_CONTROLLER_BUTTON_DPAD_LEFT,
            SDL_CONTROLLER_BUTTON_DPAD_RIGHT};
        const float dirs[][2] = {{0,1},{0,-1},{-1,0},{1,0}};
        unsigned i;
        assert(win);
        dw4_input_init(&in);
        for (i = 0; i < 4; i++) {
            SDL_Event e; SDL_zero(e);
            e.type = SDL_CONTROLLERBUTTONDOWN;
            e.cbutton.button = buttons[i];
            e.cbutton.state = SDL_PRESSED;
            assert(SDL_PushEvent(&e) == 1);
            assert(dw4_window_pump(win, &in));
            axes(&in, dirs[i][0], dirs[i][1]);
            walk(&in, 0, 0); /* a physical D-pad press never walks the player */
            e.type = SDL_CONTROLLERBUTTONUP;
            e.cbutton.state = SDL_RELEASED;
            assert(SDL_PushEvent(&e) == 1);
            assert(dw4_window_pump(win, &in));
            axes(&in, 0, 0);
        }
        SDL_Event life;memset(&life,0,sizeof(life));life.type=SDL_WINDOWEVENT;
        for (Uint32 id=1;id<1024 && !life.window.windowID;id++)
            if (SDL_GetWindowFromID(id) &&
                !strcmp(SDL_GetWindowTitle(SDL_GetWindowFromID(id)),"input test"))
                life.window.windowID=id;
        assert(life.window.windowID);
        life.window.event=SDL_WINDOWEVENT_FOCUS_LOST;
        assert(SDL_PushEvent(&life)==1 && dw4_window_pump(win,&in));
        assert(in.focus_lost && in.focus_pause && !in.cross);
        life.window.event=SDL_WINDOWEVENT_FOCUS_GAINED;
        assert(SDL_PushEvent(&life)==1 && dw4_window_pump(win,&in));
        assert(!in.focus_lost && in.focus_pause); /* loss edge remains visible to caller */
        life.type=SDL_KEYDOWN;life.key.repeat=0;life.key.keysym.scancode=SDL_SCANCODE_R;
        assert(SDL_PushEvent(&life)==1 && dw4_window_pump(win,&in) && in.resume);
#if SDL_VERSION_ATLEAST(2,0,14)
        /* A physical pad on the machine keeps the "all pads gone" state from ever being reached: only check the disconnect edge when none is present. */
        const int physical_pads=SDL_NumJoysticks();
        int virtual_pad=SDL_JoystickAttachVirtual(SDL_JOYSTICK_TYPE_GAMECONTROLLER,6,15,0);
        assert(virtual_pad>=0 && SDL_IsGameController(virtual_pad));
        assert(dw4_window_pump(win,&in) && !in.disconnected);
        assert(SDL_JoystickDetachVirtual(virtual_pad)==0);
        assert(dw4_window_pump(win,&in) && (physical_pads>0 || in.disconnected));
        virtual_pad=SDL_JoystickAttachVirtual(SDL_JOYSTICK_TYPE_GAMECONTROLLER,6,15,0);
        assert(virtual_pad>=0 && dw4_window_pump(win,&in) && !in.disconnected);
        assert(SDL_JoystickDetachVirtual(virtual_pad)==0);
#endif
        dw4_window_close(win);
    }
#endif
    puts("menu input: D-pad press/release, stick fallback, drift priority and scripted holds OK");
    return 0;
}
