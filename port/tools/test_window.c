/* A boot window must accept a movie-sized frame, then a title-sized frame. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dw4/window.h"

int main(void)
{
    dw4_window *win;
    dw4_fb fb = {0};
    const int sizes[][2] = {{1280, 960}, {640, 480}, {1280, 960}};
    int i, ok = 1;
    if (!dw4_window_built()) {
        puts("window size transition: SDL unavailable, skipped");
        return 0;
    }
    win = dw4_window_open(1280, 960, "size transition", 1);
    if (!win)
        return 1;
    for (i = 0; i < 3; i++) {
        fb.w = sizes[i][0];
        fb.h = sizes[i][1];
        fb.rgba = malloc((size_t)fb.w * fb.h * 4);
        if (!fb.rgba) { ok = 0; break; }
        memset(fb.rgba, 255, (size_t)fb.w * fb.h * 4);
        if (dw4_window_present(win, &fb) != 0 || dw4_window_order_ok(win) != 1)
            ok = 0;
        free(fb.rgba);
    }
    dw4_window_close(win);
    puts(ok ? "window size transition: ok" : "window size transition: FAILED");
    return ok ? 0 : 1;
}
