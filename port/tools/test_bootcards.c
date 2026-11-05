#include "dw4/frontui.h"
#include "dw4/png.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    dw4_mount m;
    dw4_fb fb;
    assert(!dw4_mount_open(&m, argc > 1 ? argv[1] : "../local/extracted"));
    assert(!dw4_fb_init(&fb, 640, 448));
    dw4_frontui *b = dw4_frontui_open_card(&m, 1, 600, "j_bandailogo");
    dw4_frontui *r = dw4_frontui_open_card(&m, 0, 802, "j_rating");
    assert(b && r);
    assert(dw4_frontui_items(b) == 2 && dw4_frontui_textures(b) == 2);
    assert(dw4_frontui_items(r) == 2 && dw4_frontui_textures(r) == 2);
    uint8_t *previous = malloc(640 * 448 * 4);
    assert(previous);
    memset(previous, 0, 640 * 448 * 4);
    for (int i = 0; i < 3; ++i) {
        dw4_frontui *u = i ? r : b;
        dw4_frontui_card_sample(u, i * 10, 128);
        dw4_fb_clear(&fb, 0, 0, 0);
        assert(dw4_frontui_draw(u, &fb, -1) > 0);
        int lit = 0;
        for (int p = 0; p < 640 * 448; ++p)
            if (fb.rgba[p * 4] || fb.rgba[p * 4 + 1] || fb.rgba[p * 4 + 2]) ++lit;
        assert(lit > 1000 && lit < 100000);
        assert(memcmp(previous, fb.rgba, 640 * 448 * 4));
        memcpy(previous, fb.rgba, 640 * 448 * 4);
        if (argc > 2) {
            char path[1024];
            snprintf(path, sizeof(path), "%s/bootcard%d.png", argv[2], i);
            assert(!dw4_png_write(path, fb.rgba, 640, 448));
        }
        dw4_frontui_card_sample(u, i * 10, 0);
        dw4_fb_clear(&fb, 0, 0, 0);
        dw4_frontui_draw(u, &fb, -1);
        for (int p = 0; p < 640 * 448; ++p)
            assert(!(fb.rgba[p * 4] | fb.rgba[p * 4 + 1] | fb.rgba[p * 4 + 2]));
    }
    free(previous);
    dw4_frontui_close(b); dw4_frontui_close(r);
    dw4_fb_free(&fb); dw4_mount_close(&m);
    puts("boot cards: original Bandai / Alchemy / Sofdec+ADX assets and hidden fades ok");
    return 0;
}
