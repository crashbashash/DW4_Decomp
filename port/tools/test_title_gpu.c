/* Compare the game's animated title materials at opening and loop poses. */
#include "dw4/frontlayer.h"
#include "dw4/gl_render.h"
#include "dw4/png.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    const unsigned frames[] = {8, 64, 160, 208, 240, 300, 359};
    const char *roms = argc > 1 ? argv[1] : "../local/extracted";
    int w = argc > 3 ? atoi(argv[3]) : 640, h = argc > 4 ? atoi(argv[4]) : 448;
    dw4_mount mount;
    dw4_frontlayer *cpu = NULL, *gpu = NULL;
    dw4_fb a = {0}, b = {0};
    const char *renderer;
    unsigned fi;
    int bad = 0;
    if (!dw4_gl_built()) {
        puts("title GPU: GLES unavailable, skipped");
        return 0;
    }
    if (dw4_mount_open(&mount, roms))
        return 1;
    cpu = dw4_frontlayer_open(&mount);
    gpu = dw4_frontlayer_open(&mount);
    if (!cpu || !gpu || dw4_fb_init(&a, w, h) || dw4_fb_init(&b, w, h))
        return 1;
    renderer = dw4_frontlayer_enable_gpu(gpu, w, h);
    if (!renderer) {
        puts("title GPU: EGL unavailable, skipped");
    } else {
        printf("title GPU renderer: %s\n", renderer);
        for (fi = 0; fi < sizeof frames / sizeof frames[0]; fi++) {
            size_t i, far = 0, pixels = (size_t)w * h;
            unsigned long long sum = 0;
            int max = 0;
            dw4_frontlayer_set_engine(cpu, (long long)frames[fi] * 1000000000LL / 60);
            dw4_frontlayer_set_engine(gpu, (long long)frames[fi] * 1000000000LL / 60);
            dw4_fb_clear(&a, 20, 30, 40);
            dw4_fb_clear(&b, 20, 30, 40);
            dw4_frontlayer_draw(cpu, &a);
            dw4_frontlayer_draw(gpu, &b);
            if (!dw4_frontlayer_gpu_info(gpu)) {
                puts("title GPU: unexpected CPU fallback");
                bad++;
                break;
            }
            for (i = 0; i < pixels; i++) {
                int c, pmax = 0;
                for (c = 0; c < 3; c++) {
                    int delta = abs(a.rgba[4 * i + c] - b.rgba[4 * i + c]);
                    sum += delta;
                    if (delta > pmax)
                        pmax = delta;
                }
                if (pmax > max)
                    max = pmax;
                if (pmax > 4)
                    far++;
            }
            double mean = (double)sum / (pixels * 3), percent = 100.0 * far / pixels;
            int ok = mean <= 1.0 && percent <= 1.0;
            printf("title GPU frame %3u %dx%d: mean delta %.4f, >4/channel %.3f%%, max %d %s\n",
                   frames[fi], w, h, mean, percent, max, ok ? "ok" : "FAILED");
            bad += !ok;
            if (argc > 2) {
                char path[4096];
                snprintf(path, sizeof path, "%s/cpu-%03u.png", argv[2], frames[fi]);
                if (dw4_png_write(path, a.rgba, w, h))
                    bad++;
                snprintf(path, sizeof path, "%s/gpu-%03u.png", argv[2], frames[fi]);
                if (dw4_png_write(path, b.rgba, w, h))
                    bad++;
            }
        }
    }
    dw4_frontlayer_close(cpu);
    dw4_frontlayer_close(gpu);
    dw4_fb_free(&a);
    dw4_fb_free(&b);
    dw4_mount_close(&mount);
    return bad ? 1 : 0;
}
