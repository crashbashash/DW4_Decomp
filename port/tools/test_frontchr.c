/* Naming boundaries and cancellation, using the real asset-backed screen. */
#include "dw4/frontchr.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dw4/png.h"

static void snapshot(dw4_frontchr *c, const char *roms, const char *name)
{
    const char *out = getenv("DW4_CHR_TEST_FRAMES");
    dw4_fb fb;
    dw4_fefont font = {0};
    char path[1024];
    if (!out) return;
    assert(!dw4_fb_init(&fb, 640, 448));
    assert(!dw4_fefont_load(&font, roms));
    dw4_fb_clear(&fb, 24, 28, 36);
    dw4_frontchr_draw(c, &fb, 0, &font);
    snprintf(path, sizeof path, "%s/%s.png", out, name);
    assert(!dw4_png_write(path, fb.rgba, 640, 448));
    dw4_fefont_free(&font);
    dw4_fb_free(&fb);
}

static int region_diff(const dw4_fb *a, const dw4_fb *b, int x, int y, int w, int h)
{
    int row, col, channel;
    /* The translucent window admits small changes from the moving backdrop.
     * Cursor motion changes foreground pixels much more than that. */
    for (row = y; row < y+h; row++) for (col = x; col < x+w; col++)
        for (channel = 0; channel < 3; channel++) {
            int offset = (row*a->w+col)*4 + channel;
            if (abs((int)a->rgba[offset] - b->rgba[offset]) > 25) return 1;
        }
    return 0;
}

static void cursor_animation(dw4_frontchr *c, const char *roms)
{
    dw4_fb a, b;
    dw4_fefont font = {0};
    int f, white = 0, grey = 0, x, y;
    assert(!dw4_fb_init(&a, 640, 448));
    assert(!dw4_fb_init(&b, 640, 448));
    assert(!dw4_fefont_load(&font, roms));
    dw4_frontchr_reset(c);
    dw4_frontchr_species(c, 0);
    dw4_frontchr_begin_name(c);
    dw4_frontchr_name_input(c, 0, 0, 1, 0, 0); /* white a, grey candidate a */
    for (f = 0; f <= 36; f++) {
        if (f == 16) dw4_frontchr_name_input(c, 1, 0, 0, 0, 0);
        dw4_fb_clear(&b, 24, 28, 36);
        dw4_frontchr_draw(c, &b, 0, &font);
        if (f == 0 || f == 16 || f == 28)
            memcpy(a.rgba, b.rgba, 640*448*4);
        if (f == 8) {
            /* PS2 capture 13: bright rim must cover both the dark backing and
             * the portrait corners. Mesh-average depth loses this circular mask. */
            const int rim[2][2] = {{309,35}, {290,53}};
            for (int k = 0; k < 2; k++) {
                const uint8_t *pixel = b.rgba + (rim[k][1]*640+rim[k][0])*4;
                assert(abs(pixel[0]-249) <= 2);
                assert(abs(pixel[1]-110) <= 2 && abs(pixel[2]-110) <= 2);
            }
            assert(!region_diff(&a, &b, 78, 10, 140, 31)); /* idle name cursor */
            assert(region_diff(&a, &b, 19, 66, 33, 32)); /* mode outline pulses */
            assert(region_diff(&a, &b, 84, 66, 33, 32)); /* key outline pulses */
            for (y = 22; y < 38; y++) for (x = 87; x < 94; x++) {
                int v = b.rgba[(y*640+x)*4];
                int g = b.rgba[(y*640+x+17)*4];
                if (v > white) white = v;
                if (g > grey) grey = g;
            }
            assert(white > grey + 40);
        }
        if (f == 21) assert(region_diff(&a, &b, 98, 10, 25, 31));
        if (f == 36) assert(!region_diff(&a, &b, 78, 10, 140, 31));
    }
    snapshot(c, roms, "name-cursor-colours");
    dw4_fb_free(&a);
    dw4_fb_free(&b);
    dw4_fefont_free(&font);
}

static unsigned sound_events;
static const char *sound_model, *sound_action;
static void capture_sound(void *unused, const char *model, const char *action)
{
    (void)unused; sound_events++; sound_model = model; sound_action = action;
}

int main(int argc, char **argv)
{
    dw4_mount m;
    dw4_frontchr *c;
    int i;
    if (argc != 2 || dw4_mount_open(&m, argv[1]))
        return 2;
    c = dw4_frontchr_open(&m);
    assert(c);
    dw4_frontchr_set_sound(c, capture_sound, NULL);
    dw4_frontchr_species(c, 2);
    dw4_frontchr_begin_name(c);
    snapshot(c, argv[1], "name-empty");
    unsigned before = sound_events;
    assert(!dw4_frontchr_name_input(c, 0, 0, 0, 0, 1));
    assert(sound_events == before);
    assert(dw4_frontchr_phase(c) == DW4_CHR_NAME); /* empty Start */
    for (i = 0; i < DW4_CHR_NAME_MAX + 3; i++)
        dw4_frontchr_name_input(c, 0, 0, 1, 0, 0);
    assert(strlen(dw4_frontchr_name(c)) == DW4_CHR_NAME_MAX);
    assert(sound_events - before == DW4_CHR_NAME_MAX); /* full-name Cross is silent */
    assert(!strcmp(sound_model, "j_namecursorus") && !strcmp(sound_action, "NAMEON00"));
    for (i = 0; i < DW4_CHR_NAME_MAX - 1; i++)
        dw4_frontchr_name_input(c, 0, 0, 0, 1, 0);
    dw4_frontchr_name_input(c, -1, 0, 0, 0, 0); /* wrap left a -> z */
    dw4_frontchr_name_input(c, 0, 0, 1, 0, 0);
    assert(!strcmp(dw4_frontchr_name(c), "az"));
    dw4_frontchr_name_input(c, 0, 1, 0, 0, 0); /* retail Down: lowercase -> uppercase */
    dw4_frontchr_name_input(c, 0, 0, 1, 0, 0);
    assert(!strcmp(dw4_frontchr_name(c), "azA"));
    dw4_frontchr_name_input(c, 0, 0, 0, 0, 1);
    assert(dw4_frontchr_phase(c) == DW4_CHR_QUESTION);
    snapshot(c, argv[1], "name-question");
    dw4_frontchr_name_input(c, 0, 0, 1, 0, 0);
    assert(dw4_frontchr_phase(c) == DW4_CHR_CONFIRM);
    snapshot(c, argv[1], "name-confirm");
    /* The confirmation selector is pack geometry, present even without fonts.
     * Its pale diamond sits beside the selected row, independent of glyphs. */
    {
        dw4_fb yes, no;
        assert(!dw4_fb_init(&yes, 640, 448));
        assert(!dw4_fb_init(&no, 640, 448));
        dw4_frontchr_draw(c, &yes, 0, NULL);
        const unsigned char *tip = yes.rgba + (159*640+29)*4;
        assert(tip[0] > 120 && tip[1] > 120 && tip[2] > 120);
        dw4_frontchr_name_input(c, 0, -1, 0, 0, 0);
        dw4_frontchr_draw(c, &no, 0, NULL);
        tip = no.rgba + (176*640+29)*4;
        assert(tip[0] > 120 && tip[1] > 120 && tip[2] > 120);
        assert(region_diff(&yes, &no, 22, 151, 15, 32));
        snapshot(c, argv[1], "name-confirm-no");
        dw4_fb_free(&yes); dw4_fb_free(&no);
    }
    dw4_frontchr_name_input(c, 0, 0, 1, 0, 0);
    assert(dw4_frontchr_phase(c) == DW4_CHR_NAME);
    assert(!strcmp(dw4_frontchr_name(c), "azA"));
    dw4_frontchr_name_input(c, 0, 0, 0, 0, 1);
    dw4_frontchr_name_input(c, 0, 0, 0, 1, 0);
    assert(dw4_frontchr_phase(c) == DW4_CHR_NAME);
    dw4_frontchr_name_input(c, 0, 0, 0, 0, 1);
    dw4_frontchr_name_input(c, 0, 0, 1, 0, 0);
    dw4_frontchr_name_input(c, 0, 0, 1, 0, 0);
    assert(dw4_frontchr_phase(c) == DW4_CHR_CREATED);
    snapshot(c, argv[1], "name-created");
    assert(!dw4_frontchr_name_input(c, 0, 0, 1, 0, 0));
    assert(dw4_frontchr_name_input(c, 0, 0, 0, 0, 1) == 1);
    {
        dw4_frontchr *login = dw4_frontchr_open(&m);
        dw4_fb fb;
        int frame;
        assert(login && !dw4_fb_init(&fb, 320, 240));
        dw4_frontchr_species(login, 2);
        dw4_frontchr_begin_name(login);
        dw4_frontchr_name_input(login, 0, 0, 1, 0, 0);
        dw4_frontchr_name_input(login, 0, 0, 0, 0, 1);
        dw4_frontchr_name_input(login, 0, 0, 1, 0, 0);
        dw4_frontchr_name_input(login, 0, 0, 1, 0, 0);
        dw4_frontchr_begin_login(login);
        for (frame = 0; frame <= 60; frame++) {
            assert(!dw4_frontchr_login_done(login));
            assert(!dw4_frontchr_name_input(login, 1, -1, 1, 1, 1));
            assert(dw4_frontchr_phase(login) == DW4_CHR_CREATED);
            assert(!strcmp(dw4_frontchr_name(login), "a"));
            dw4_fb_clear(&fb, 24, 28, 36);
            dw4_frontchr_draw(login, &fb, 0, NULL);
        }
        assert(dw4_frontchr_login_done(login));
        for (frame = 0; frame < fb.w*fb.h; frame++)
            assert(!(fb.rgba[4*frame] | fb.rgba[4*frame+1] | fb.rgba[4*frame+2]));
        dw4_frontchr_begin_login(login); /* repeated Start cannot restart CLOSE */
        assert(dw4_frontchr_login_done(login));
        dw4_fb_free(&fb);
        dw4_frontchr_close(login);
    }
    dw4_frontchr_name_input(c, 0, 0, 0, 1, 0);
    assert(dw4_frontchr_phase(c) == DW4_CHR_NAME);
    assert(!strcmp(dw4_frontchr_name(c), "azA"));
    dw4_frontchr_name_input(c, 0, 0, 0, 1, 0);
    assert(!strcmp(dw4_frontchr_name(c), "az"));
    dw4_frontchr_species(c, 1);
    dw4_frontchr_begin_name(c);
    assert(!*dw4_frontchr_name(c));
    for (i = 0; i < 18; i++) dw4_frontchr_name_input(c, 1, 0, 0, 0, 0);
    dw4_frontchr_name_input(c, -1, 0, 0, 0, 0);
    dw4_frontchr_name_input(c, 0, 0, 1, 0, 0);
    assert(!strcmp(dw4_frontchr_name(c), "r"));
    snapshot(c, argv[1], "name-scroll-back");
    dw4_frontchr_name_input(c, 0, 0, 0, 1, 0);
    dw4_frontchr_name_input(c, 0, 0, 0, 1, 0);
    assert(dw4_frontchr_phase(c) == DW4_CHR_SELECT);
    /* Render a switch alongside an unchanged screen. The first switch frame
     * must still contain the outgoing model, and uncovered portrait pixels
     * must retain the backdrop rather than an opaque black viewport clear. */
    {
        dw4_frontchr *steady = dw4_frontchr_open(&m);
        dw4_fb frame, reference;
        dw4_fefont font = {0};
        const char *output = getenv("DW4_CHR_TEST_FRAMES");
        int f, y;
        assert(steady);
        assert(!dw4_fb_init(&frame, 640, 448));
        assert(!dw4_fb_init(&reference, 640, 448));
        if (output) assert(!dw4_fefont_load(&font, argv[1]));
        dw4_frontchr_reset(c);
        dw4_frontchr_species(c, 0);
        dw4_frontchr_species(steady, 0);
        for (f = 0; f < 150; f++) {
            if (f == 60) dw4_frontchr_species(c, 3);
            if (f == 105) dw4_frontchr_species(c, 2);
            if (f == 108) dw4_frontchr_species(c, 1); /* interrupted fade */
            if (f == 110) dw4_frontchr_species(c, 0);
            dw4_fb_clear(&frame, 24, 28, 36);
            dw4_frontchr_draw(c, &frame, 0, &font);
            if (f <= 60) {
                dw4_fb_clear(&reference, 24, 28, 36);
                dw4_frontchr_draw(steady, &reference, 0, &font);
            }
            if (f == 59) {
                const uint8_t *p = frame.rgba + (50*640+160)*4;
                assert(p[0] > 0 && p[1] > 0 && p[2] > 0);
            }
            if (f == 60)
                for (y = 70; y < 135; y++)
                    assert(!memcmp(frame.rgba + (y*640+125)*4,
                                   reference.rgba + (y*640+125)*4, 70*4));
            if (output) {
                char path[1024];
                snprintf(path, sizeof path, "%s/%03d.png", output, f);
                assert(!dw4_png_write(path, frame.rgba, 640, 448));
            }
        }
        dw4_fefont_free(&font);
        dw4_fb_free(&frame);
        dw4_fb_free(&reference);
        dw4_frontchr_close(steady);
    }
    cursor_animation(c, argv[1]);
    dw4_frontchr_close(c);
    dw4_mount_close(&m);
    puts("character screen: naming, confirmation, transparent portrait and outgoing selection retention OK");
    return 0;
}
