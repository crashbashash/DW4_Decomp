/* Render one greeting page in isolation and export its native UI submission. */
#include "dw4/lobbyui.h"
#include "dw4/png.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    dw4_mount mount;
    dw4_scene scene;
    dw4_fb fb;
    uint32_t size;
    if (argc != 5 && argc != 6) {
        fprintf(stderr, "usage: lobby_ui_frame ROMS PAGE PNG VERTICES.tsv [TEXTURE_DIR]\n");
        return 2;
    }
    int page = atoi(argv[2]);
    if (page < 39 || page > 53 || dw4_mount_open(&mount, argv[1]))
        return 1;
    const uint8_t *blob = dw4_mount_entry(&mount, 0, 820, &size, NULL);
    if (!blob || dw4_scene_load(&scene, blob, size) || dw4_fb_init(&fb, 640, 448))
        return 1;
    dw4_lobbyui *ui = dw4_lobbyui_open(&mount, &scene, blob, size);
    if (!ui)
        return 1;
    dw4_lobbyui_start(ui);
    for (unsigned ticks = 0; dw4_lobbyui_message(ui) != page; ticks++) {
        if (ticks > 2000)
            return 1;
        dw4_lobbyui_tick(ui, dw4_lobbyui_message(ui) >= 39 && dw4_lobbyui_message(ui) < page);
    }
    dw4_fb_clear(&fb, 32, 32, 32);
    dw4_lobbyui_draw(ui, &fb);
    if (dw4_png_write(argv[3], fb.rgba, 640, 448))
        return 1;
    FILE *out = fopen(argv[4], "w");
    if (!out)
        return 1;
    unsigned n;
    const dw4_ui_draw *d = dw4_lobbyui_draws(ui, &n);
    fputs("x\ty\tu\tv\tr\tg\tb\ta\tw\th\n", out);
    for (unsigned i = 0; i < n; i++)
        for (unsigned e = 0; e < 3; e++)
            fprintf(out, "%.6f\t%.6f\t%.6f\t%.6f\t%u\t%u\t%u\t%u\t%d\t%d\n", d[i].v[e][0],
                    d[i].v[e][1], d[i].v[e][2], d[i].v[e][3], d[i].rgba[e][0], d[i].rgba[e][1],
                    d[i].rgba[e][2], d[i].rgba[e][3], d[i].tex->w, d[i].tex->h);
    if (argc == 6) {
        const dw4_tex *written[4] = {0};
        unsigned nw = 0;
        for (unsigned i = 0; i < n; i++) {
            const dw4_tex *tex = d[i].tex;
            int seen = 0;
            for (unsigned j = 0; j < nw; j++)
                if (written[j]->w == tex->w && written[j]->h == tex->h)
                    seen = 1;
            if (seen)
                continue;
            if (nw == 4)
                return 1;
            written[nw++] = tex;
            char path[4096];
            snprintf(path, sizeof path, "%s/%dx%d.png", argv[5], tex->w, tex->h);
            if (dw4_png_write(path, tex->rgba, tex->w, tex->h))
                return 1;
        }
    }
    fclose(out);
    dw4_lobbyui_close(ui);
    dw4_scene_close(&scene);
    dw4_fb_free(&fb);
    dw4_mount_close(&mount);
    return 0;
}
