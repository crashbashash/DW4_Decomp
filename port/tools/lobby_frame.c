/* Deterministic arrival frame and pre-rasterisation GS-style vertex export. */
#include "dw4/lobby.h"
#include "dw4/png.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* RGB-only identity: GS alpha uses a different range. Cache by immutable texture. */
static uint32_t texture_hash(const dw4_tex *tex)
{
    uint32_t hash = 2166136261u;
    if (!tex || !tex->rgba) return 0;
    for (int i = 0; i < tex->w*tex->h; i++) for (int c = 0; c < 3; c++)
        hash = (hash ^ tex->rgba[4*i+c])*16777619u;
    return hash;
}
int main(int argc, char **argv)
{
    dw4_mount mount;
    dw4_fb fb;
    dw4_lobby *l;
    unsigned frame, count;
    const dw4_layer_draw *draw;
    FILE *out;
    int ui = 0, hard = 1;
    if (argc < 5) { fprintf(stderr, "usage: lobby_frame ROMS FRAME PNG VERTICES.tsv [--ui] [--soft|--hard]\n"); return 2; }
    for (int i=5;i<argc;i++) {
        if (!strcmp(argv[i],"--ui")) ui=1;
        else if (!strcmp(argv[i],"--soft")) hard=0;
        else if (!strcmp(argv[i],"--hard")) hard=1;
        else return 2;
    }
    frame = (unsigned)strtoul(argv[2], NULL, 10);
    if (dw4_mount_open(&mount, argv[1]) || dw4_fb_init(&fb, 640, 448)) return 1;
    l = dw4_lobby_open(&mount, 0, "aa");
    if (!l) return 1;
    dw4_lobby_set_light(l,hard);
    for (unsigned i = 0; i <= frame; i++) dw4_lobby_tick(l, 0);
    if (dw4_lobby_draw(l, &fb, frame, ui ? &(dw4_fefont){.have=1} : NULL) < 0 || dw4_png_write(argv[3], fb.rgba, 640, 448)) return 1;
    out = fopen(argv[4], "w");
    if (!out) return 1;
    fputs("x\ty\tu\tv\tr\tg\tb\ta\tblend\tzmask\tdepth\tfog\ttexture_rgb_hash\tshadow\n", out);
    draw = dw4_lobby_last_draws(l, &count);
    const dw4_tex *textures[256];
    uint32_t hashes[256];
    unsigned ntextures = 0;
    for (unsigned i = 0; i < count; i++) for (unsigned e = 0; e < 3; e++) {
        const dw4_layer_draw *d = draw+i;
        unsigned t;
        for (t = 0; t < ntextures && textures[t] != d->tex; t++);
        if (t == ntextures) {
            if (ntextures == 256) return 1;
            textures[t] = d->tex; hashes[t] = texture_hash(d->tex); ntextures++;
        }
        fprintf(out, "%.6f\t%.6f\t%.6f\t%.6f\t%u\t%u\t%u\t%u\t%u\t%d\t%.6f\t%.0f\t%08x\t%d\n",
                d->v[e][0], d->v[e][1], d->v[e][2]/d->v[e][4], d->v[e][3]/d->v[e][4],
                d->rgba[e][0],d->rgba[e][1],d->rgba[e][2],d->rgba[e][3],d->blend,d->no_depth_write,16777216.0f/d->z[e],d->f[e],hashes[t],d->aref==-1 && d->fog==0 && d->no_depth_write && d->blend==1);
    }
    fclose(out);
    dw4_lobby_close(l); dw4_fb_free(&fb); dw4_mount_close(&mount);
    return 0;
}
