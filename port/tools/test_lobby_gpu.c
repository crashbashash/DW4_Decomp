/* Real lobby assets: CPU oracle comparison and warm rendering benchmark.
 * Timings include scene/pose work, rasterisation and GPU readback, not presentation. */
#define _POSIX_C_SOURCE 200809L
#include "dw4/lobby.h"
#include "dw4/gl_layer.h"
#include "dw4/gpupolicy.h"
#include <assert.h>
#include "dw4/png.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
static double ms(void)
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * 1000.0 + t.tv_nsec / 1e6;
}
static int order(const void *a, const void *b)
{
    double x = *(const double *)a, y = *(const double *)b;
    return (x > y) - (x < y);
}
int main(int argc, char **argv)
{
    const char *roms = argc > 1 ? argv[1] : "../local/extracted";
    const char *out = argc > 2 ? argv[2] : NULL;
    int w = argc > 3 ? atoi(argv[3]) : 640, h = argc > 4 ? atoi(argv[4]) : 448;
    int samples = argc > 5 ? atoi(argv[5]) : 20, bad = 0;
    dw4_mount mount;
    dw4_fb fb[2] = {{0}};
    dw4_fefont font = {.have = 1}; /* lobby loads its own font faces */
    if (samples < 1 || samples > 10000 || w < 1 || h < 1) return 2;
    if (dw4_mount_open(&mount, roms) || dw4_fb_init(&fb[0], w, h) || dw4_fb_init(&fb[1], w, h)) return 1;
    double *times = malloc((size_t)samples * sizeof *times);
    if (!times) return 1;
    for (unsigned species = 0; species < 4; species++) {
        dw4_lobby *l[2] = {dw4_lobby_open(&mount, species, "aa"), dw4_lobby_open(&mount, species, "aa")};
        if (!l[0] || !l[1]) return 1;
        const char *renderer = dw4_lobby_enable_gpu(l[1], w, h);
        if (!renderer) {
            puts("lobby GPU: EGL unavailable, skipped");
            dw4_lobby_close(l[0]); dw4_lobby_close(l[1]);
            break;
        }
        int hardware=dw4_gpu_policy_hardware(renderer);
        if (!species) printf("lobby GPU renderer: %s; %dx%d; %d warm samples\n", renderer, w, h, samples);
        unsigned next = 0;
        const unsigned frames[] = {24, 63, 180, 204, 229, 242, 350, 354, 360, 392, 600, 604, 642, 1100};
        for (unsigned f = 0; f < sizeof frames / sizeof *frames; f++) {
            unsigned frame = frames[f];
            while (next <= frame) {
                for (int i = 0; i < 2; i++) dw4_lobby_tick(l[i], next > 600);
                next++;
            }
            /* Cover saved Soft and Hard across entry, portals, greeting and HUD. */
            for (int i=0;i<2;i++) dw4_lobby_set_light(l[i], f%2);
            for (int i = 0; i < 2; i++) if (dw4_lobby_draw(l[i], &fb[i], frame, &font) < 0) return 1;
            if (frame == 1100 && (!dw4_lobby_intro_done(l[0]) || !dw4_lobby_intro_done(l[1]))) return 1;
            unsigned n[2];
            const dw4_layer_draw *d[2];
            for (int i = 0; i < 2; i++) d[i] = dw4_lobby_last_draws(l[i], n+i);
            /* Textures have different allocations; all submitted vertex/state bytes must agree. */
            if (n[0] != n[1]) {fprintf(stderr,"submission count mismatch species %u frame %u: %u/%u\n",species,frame,n[0],n[1]);return 1;}
            for (unsigned j = 0; j < n[0]; j++) {
                dw4_layer_draw a = d[0][j], b = d[1][j];
                a.tex = b.tex = NULL;
                if (memcmp(&a, &b, sizeof a)) {fprintf(stderr,"submission mismatch species %u frame %u triangle %u\n",species,frame,j);return 1;}
            }
            size_t pixels = (size_t)w*h, far = 0;
            double sum = 0;
            for (size_t p = 0; p < pixels; p++) {
                int max = 0;
                for (int c = 0; c < 3; c++) {
                    int delta = abs(fb[0].rgba[4*p+c]-fb[1].rgba[4*p+c]);
                    sum += delta;
                    if (delta > max) max = delta;
                }
                far += max > 4;
            }
            double mean = sum/(3*pixels), percent = 100.0*far/pixels;
            printf("lobby species %u frame %u: %u triangles, RGB MAE %.4f, >4/channel %.3f%%\n", species, frame, n[0], mean, percent);
            bad |= mean > 1 || percent > 1;
            if (out) for (int i = 0; i < 2; i++) {
                char path[4096];
                snprintf(path, sizeof path, "%s/%s-%u-%u.png", out, i ? "gpu" : "cpu", species, frame);
                if (dw4_png_write(path, fb[i].rgba, w, h)) return 1;
            }
            if(frame==350) for(int i=0;i<2;i++) for(unsigned portal=0;portal<4;portal++) {
                if(dw4_lobby_portal_command(l[i],portal,"SQ_POWERON") ||
                   dw4_lobby_portal_command(l[i],portal,"SQ_SWON")) return 1;
            }
            if(frame==392) for(int i=0;i<2;i++) if(dw4_lobby_actor_visible(l[i],1,0)) return 1;
            if(frame==600) for(int i=0;i<2;i++) {
                if(dw4_lobby_actor_visible(l[i],1,1)) return 1;
                for(unsigned portal=0;portal<4;portal++)
                    if(dw4_lobby_portal_command(l[i],portal,"SQ_SWOF")) return 1;
            }
        }
        const char *swaps[]={"w_common04","w_common07"};char error[256];
        for(unsigned swap=0;swap<4;swap++){
            for(unsigned i=0;i<2;i++)if(dw4_lobby_weapon(l[i],&mount,swaps[swap%2],error,sizeof error)){fprintf(stderr,"swap: %s\n",error);return 1;}
            if(!dw4_lobby_gpu_info(l[1]))return 1;
            for(unsigned i=0;i<2;i++)if(dw4_lobby_draw(l[i],&fb[i],0,&font)<0)return 1;
            if(!dw4_lobby_gpu_info(l[1]))return 1;
            for(unsigned i=0;i<2;i++) {
                unsigned parts=swap%2?1:2;assert(dw4_lobby_weapon_parts(l[i])==parts);
                for(unsigned part=0;part<parts;part++) {
                    dw4_lobby_weapon_part_state state;assert(!dw4_lobby_weapon_part(l[i],part,&state));
                    assert(!strcmp(state.bone,part?"LArm04":"RArm04") && state.triangles && state.submitted_triangles);
                }
            }
            if(out && !swap)for(unsigned i=0;i<2;i++) {
                char path[4096];snprintf(path,sizeof path,"%s/%s-paired-guns-%u.png",out,i?"gpu":"cpu",species);
                if(dw4_png_write(path,fb[i].rgba,w,h))return 1;
            }
            size_t pixels=(size_t)w*h,far=0;double sum=0;
            for(size_t p=0;p<pixels;p++){
                int maximum=0;for(unsigned c=0;c<3;c++){int delta=abs(fb[0].rgba[4*p+c]-fb[1].rgba[4*p+c]);sum+=delta;if(delta>maximum)maximum=delta;}
                far+=maximum>4;
            }
            double mean=sum/(3*pixels),percent=100.0*far/pixels;
            printf("lobby GPU species %u swap %u: retained GPU, RGB MAE %.4f, >4/channel %.3f%%\n",species,swap,mean,percent);
            if(mean>1 || percent>1)bad=1;
        }
        if (!species) for (int i = 0; i < 2; i++) {
            double sum = 0;
            for (int f = -5; f < samples; f++) {
                dw4_lobby_tick(l[i], 0);
                double start = ms();
                if (dw4_lobby_draw(l[i], &fb[i], 601+f+5, &font) < 0) return 1;
                double elapsed = ms()-start;
                if (f >= 0) { times[f] = elapsed; sum += elapsed; }
            }
            qsort(times, samples, sizeof *times, order);
            printf("lobby %s draw: mean %.3f ms, p50 %.3f, p95 %.3f, max %.3f\n", i ? "GPU" : "CPU", sum/samples, times[samples/2], times[(samples-1)*95/100], times[samples-1]);
        }
        if (!species) {
            /* Replaying prepared submissions isolates GPU rasterisation/transfer
             * from scene traversal, lighting, clipping and skeletal evaluation. */
            dw4_gl_layer *g = dw4_gl_layer_open(w, h);
            unsigned count;
            const dw4_layer_draw *draw = dw4_lobby_last_draws(l[1], &count);
            if (!g) return 1;
            double sum = 0;
            for (int f = -5; f < samples; f++) {
                dw4_fb_clear(&fb[1], 0, 0, 0);
                double start = ms();
                if (dw4_gl_layer_draw(g, &fb[1], draw, count, 1, 1, -1)) return 1;
                if (f >= 0) sum += ms()-start;
            }
            printf("lobby GPU prepared world replay: mean %.3f ms (includes upload/readback; excludes UI)\n", sum/samples);
            dw4_gl_layer_close(g);
            /* A size mismatch forces draw failure: the untouched framebuffer
             * must be rendered by the CPU fallback, including the greeting. */
            if (!dw4_lobby_enable_gpu(l[1], 1, 1)) return 1;
            for (int i = 0; i < 2; i++)
                if (dw4_lobby_draw(l[i], &fb[i], 650, &font) < 0) return 1;
            if (memcmp(fb[0].rgba, fb[1].rgba, (size_t)w*h*4)) return 1;
            puts("lobby GPU: failed draw restores complete CPU frame exactly");
            if(hardware){
                assert(dw4_lobby_enable_gpu(l[1],1,1));
                dw4_gpu_policy_begin(1);
                assert(dw4_lobby_draw(l[1],&fb[1],650,&font)<0 && dw4_gpu_policy_error()[0]);
                for(unsigned kind=0;kind<DW4_CPU_KIND_COUNT;kind++)assert(!dw4_gpu_policy_cpu_count(kind));
                dw4_gpu_policy_begin(0);
                puts("lobby GPU: normal failed clear stops with zero CPU raster/composite calls");
            }
        }
        dw4_lobby_close(l[0]); dw4_lobby_close(l[1]);
    }
    free(times);
    dw4_fb_free(&fb[0]); dw4_fb_free(&fb[1]); dw4_mount_close(&mount);
    return bad ? 1 : 0;
}
