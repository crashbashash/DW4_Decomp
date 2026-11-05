/* Real menu assets: ordered panels, text, badges and animated backgrounds. */
#define _POSIX_C_SOURCE 200809L
#include "dw4/frontchr.h"
#include "dw4/frontopt.h"
#include "dw4/frontui.h"
#include "dw4/gl_render.h"
#include "dw4/gpupolicy.h"
#include "dw4/png.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
static double ms(void)
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * 1000.0 + t.tv_nsec / 1e6;
}
static int compare(dw4_fb *a, dw4_fb *b, const char *screen, const char *out)
{
    size_t pixels = (size_t)a->w * a->h, far = 0;
    double sum = 0;
    for (size_t p = 0; p < pixels; p++) {
        int mx = 0;
        for (int c = 0; c < 3; c++) {
            int d = abs(a->rgba[4 * p + c] - b->rgba[4 * p + c]);
            sum += d;
            if (d > mx)
                mx = d;
        }
        if (mx > 4)
            far++;
    }
    double mean = sum / (pixels * 3), percent = 100.0 * far / pixels;
    printf("%-18s mean %.4f, >4/channel %.3f%%\n", screen, mean, percent);
    if (out) {
        char path[4096];
        snprintf(path, sizeof path, "%s/cpu-%s.png", out, screen);
        if (dw4_png_write(path, a->rgba, a->w, a->h))
            return 1;
        snprintf(path, sizeof path, "%s/gpu-%s.png", out, screen);
        if (dw4_png_write(path, b->rgba, b->w, b->h))
            return 1;
    }
    return mean > 1 || percent > 1;
}
/* Sample only the top of the options outline, excluding its text and rotating
 * row icon: this must change while the selected row remains stationary. */
static uint64_t option_strip(const dw4_fb *fb)
{
    float scale = fb->h / 448.0f;
    uint64_t hash = 14695981039346656037ULL;
    int x0 = (int)(fb->w * .5f - 170 * scale), x1 = (int)(fb->w * .5f + 190 * scale);
    for (int y = (int)(134 * scale); y < (int)(140 * scale); ++y)
        for (int x = x0; x < x1; ++x)
            for (int c = 0; c < 3; ++c)
                hash = (hash ^ fb->rgba[((size_t)y * fb->w + x) * 4 + c]) * 1099511628211ULL;
    return hash;
}

int main(int argc, char **argv)
{
    const char *roms = argc > 1 ? argv[1] : "../local/extracted",
               *out = argc > 2 ? argv[2] : NULL;
    int w = argc > 3 ? atoi(argv[3]) : 640, h = argc > 4 ? atoi(argv[4]) : 448,
        bad = 0;
    dw4_mount mount;
    dw4_fefont font = {0};
    dw4_fb fb[2] = {{0}};
    dw4_frontchr *chr[2];
    dw4_frontopt *opt[2];
    dw4_title_host title[2]={{0}};
    dw4_frontui *ui[2];
    if (!dw4_gl_built()) {
        puts("menu GPU: GLES unavailable, skipped");
        return 0;
    }
    if (dw4_mount_open(&mount, roms) || dw4_fefont_load(&font, roms))
        return 1;
    for (int i = 0; i < 2; i++) {
        chr[i] = dw4_frontchr_open(&mount);
        opt[i] = dw4_frontopt_open(&mount);
        ui[i] = dw4_frontui_open(&mount);
        if (!chr[i] || !opt[i] || !ui[i] || dw4_fb_init(&fb[i], w, h))
            return 1;
    }
    if (!dw4_frontchr_enable_gpu(chr[1], w, h)) {
        puts("menu GPU: EGL unavailable, skipped");
        goto done;
    }
    if (!dw4_frontopt_enable_gpu(opt[1], w, h) ||
        !dw4_frontui_enable_gpu(ui[1], w, h))
        return 1;
    int hardware=dw4_gpu_policy_hardware(dw4_frontchr_gpu_info(chr[1]));
    const char *names[] = {"create",  "call",  "dorumon",  "agumon",  "veemon",
                           "guilmon", "name",  "question", "confirm", "created",
                           "options", "title", "main-menu"};
    for (int screen = 0; screen < 13; screen++) {
        for (int i = 0; i < 2; i++) {
            if (screen >= 2 && screen <= 5)
                dw4_frontchr_species(chr[i], screen - 2);
            if (screen == 6)
                dw4_frontchr_begin_name(chr[i]);
            if (screen == 7) {
                dw4_frontchr_name_input(chr[i], 0, 0, 1, 0, 0);
                dw4_frontchr_name_input(chr[i], 0, 0, 0, 0, 1);
            }
            if (screen == 8 || screen == 9)
                dw4_frontchr_name_input(chr[i], 0, 0, 1, 0, 0);
            if (screen == 10) {
                dw4_title_host_init(&title[i], 0, 1);
                dw4_frontopt_bind_title(opt[i], &title[i]);
                title[i].text = (1u << 1) | (1u << 3) | (1u << 5);
                title[i].api.model_start(&title[i], 0, T_j_optionwin02, T_SQ_BOPEN, 0);
                title[i].api.model_start(&title[i], 0, T_j_optioncursor11, T_SQ_OPEN, 0);
                title[i].api.model_start(&title[i], 0, T_j_optioncursor12, T_SQ_OPEN, 0);
            }
            if (screen >= 6 && screen <= 9)
                assert(dw4_frontchr_phase(chr[i]) == screen - 5);
            if (screen == 12)
                dw4_frontui_start(ui[i], 300LL * 1000000000 / 60);
        }
        double elapsed[2] = {0};
        uint64_t strip[2] = {0};
        for (int f = 0; f < 40; f++)
            for (int i = 0; i < 2; i++) {
                dw4_fb_clear(&fb[i], 24, 28, 36);
                if(i==1 && hardware)dw4_gpu_policy_begin(1);
                double start = ms();
                if (screen == 10) {
                    title[i].api.model_tick(&title[i]);
                    if (f == 25) {
                        title[i].api.model_play(&title[i], 0, T_j_optioncursor11, T_SQ_LINESL01, 0);
                        title[i].api.model_play(&title[i], 0, T_j_optioncursor12, T_SQ_LINERT01, 0);
                    }
                    if (f == 35) {
                        title[i].api.model_play(&title[i], 0, T_j_optioncursor11, T_SQ_LINESL03, 0);
                        title[i].api.model_close(&title[i], 0, T_j_optioncursor12, T_SQ_CLOSE, 0);
                    }
                    dw4_frontopt_draw(opt[i], &fb[i], 1, &font, 1, 1);
                    if (f == 15) strip[i] = option_strip(&fb[i]);
                    if (f == 24) assert(strip[i] != option_strip(&fb[i]));
                    if (f == 8) {
                        size_t bytes = (size_t)w * h * 4;
                        uint8_t *same = malloc(bytes);
                        assert(same);
                        memcpy(same, fb[i].rgba, bytes);
                        if(i==1 && hardware){
                            for(unsigned kind=0;kind<DW4_CPU_KIND_COUNT;kind++)assert(!dw4_gpu_policy_cpu_count(kind));
                            dw4_gpu_policy_begin(0);
                        }
                        dw4_fb_clear(&fb[i], 24, 28, 36);
                        if(i==1 && hardware)dw4_gpu_policy_begin(1);
                        dw4_frontopt_draw(opt[i], &fb[i], 1, &font, 1, 1);
                        assert(!memcmp(same, fb[i].rgba, bytes));
                        free(same); /* drawing twice must not advance any animation */
                    }
                }
                else if (screen >= 11) {
                    dw4_frontui_set_engine(ui[i],
                                           (300LL + f) * 1000000000 / 60);
                    dw4_frontui_draw(ui[i], &fb[i], f < 20 ? 0 : 1);
                } else
                    dw4_frontchr_draw(chr[i], &fb[i], screen == 1, &font);
                if(i==1 && hardware){
                    for(unsigned kind=0;kind<DW4_CPU_KIND_COUNT;kind++)assert(!dw4_gpu_policy_cpu_count(kind));
                    assert(!dw4_gpu_policy_error()[0]);dw4_gpu_policy_begin(0);
                }
                if (f >= 10)
                    elapsed[i] += ms() - start;
                if (i == 1 && (f == 0 || f == 8 || f == 20 || f == 39))
                    bad += compare(&fb[0], &fb[1], names[screen], NULL);
                if (i == 1 && screen == 10 && out && (f == 8 || f == 19 || f == 24)) {
                    char pose[64];
                    snprintf(pose, sizeof pose, "options-%02d", f);
                    bad += compare(&fb[0], &fb[1], pose, out);
                }
            }
        /* Both objects advance once per frame, retaining the same animation
         * clocks. */
        bad += compare(&fb[0], &fb[1], names[screen], out);
        printf("  %dx%d CPU %.2f ms, GPU %.2f ms\n", w, h, elapsed[0] / 30,
               elapsed[1] / 30);
        if (!dw4_frontchr_gpu_info(chr[1]) || !dw4_frontopt_gpu_info(opt[1]) ||
            !dw4_frontui_gpu_info(ui[1]))
            return 1;
    }
done:
    for (int i = 0; i < 2; i++) {
        dw4_title_host_close(&title[i]);
        dw4_frontchr_close(chr[i]);
        dw4_frontopt_close(opt[i]);
        dw4_frontui_close(ui[i]);
        dw4_fb_free(&fb[i]);
    }
    dw4_fefont_free(&font);
    dw4_mount_close(&mount);
    return bad ? 1 : 0;
}
