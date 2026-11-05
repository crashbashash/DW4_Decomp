/* dw4/movie.c — the Sofdec movie frame source; see include/dw4/movie.h. */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include "dw4/movie.h"
#include "dw4/audio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "dw4/mount.h"
#include "dw4/window.h"
#include "dw4/vk_present.h"
#include "dw4/render.h"        /* dw4_fb + dw4_render_fps: the `--fps` readout on the frame */
#include "dw4/gl_layer.h"
#include "dw4/gpupolicy.h"

struct dw4_movie {
    FILE *pipe;         /* ffmpeg's rawvideo output */
    int   w, h;
    char  tmppath[64];  /* the extracted .sfd, unlinked on close */
};

/* ffprobe the video stream's own size, so the caller gets the movie's geometry and not a guess. */
static int probe_size(const char *path, int *w, int *h)
{
    char cmd[4096];
    FILE *f;
    int rw = 0, rh = 0;
    snprintf(cmd, sizeof(cmd),
             "ffprobe -v error -select_streams v:0 -show_entries stream=width,height "
             "-of csv=p=0 '%s' 2>/dev/null", path);
    f = popen(cmd, "r");
    if (!f)
        return -1;
    if (fscanf(f, "%d,%d", &rw, &rh) != 2)
        rw = rh = 0;
    pclose(f);
    if (rw <= 0 || rh <= 0)
        return -1;
    *w = rw;
    *h = rh;
    return 0;
}

dw4_movie *dw4_movie_open(const char *roms_dir, const char *name, int *w, int *h)
{
    dw4_mount m;
    dw4_movie *mv;
    const uint8_t *p;
    uint32_t sz = 0;
    char tmpl[] = "/tmp/dw4movieXXXXXX";
    char cmd[4096];
    int fd, mw = 0, mh = 0;

    if (!roms_dir || !name || dw4_mount_open(&m, roms_dir) != 0)
        return NULL;
    p = dw4_mount_data(&m, name, &sz);
    if (!p) {
        fprintf(stderr, "movie: cannot resolve %s in %s\n", name, roms_dir);
        dw4_mount_close(&m);
        return NULL;
    }
    fd = mkstemp(tmpl);
    if (fd < 0 || write(fd, p, sz) != (ssize_t)sz) {
        if (fd >= 0) {
            close(fd);
            unlink(tmpl);
        }
        dw4_mount_close(&m);
        return NULL;
    }
    close(fd);
    dw4_mount_close(&m);

    mv = (dw4_movie *)calloc(1, sizeof(*mv));
    if (!mv) {
        unlink(tmpl);
        return NULL;
    }
    snprintf(mv->tmppath, sizeof(mv->tmppath), "%s", tmpl);
    if (probe_size(tmpl, &mw, &mh) != 0) {
        fprintf(stderr, "movie: cannot probe %s\n", name);
        dw4_movie_close(mv);
        return NULL;
    }
    mv->w = mw;
    mv->h = mh;
    /* The first video stream, decoded to the raw 24-bit pixels the presenter converts. */
    snprintf(cmd, sizeof(cmd),
             "ffmpeg -v error -i '%s' -map 0:v:0 -f rawvideo -pix_fmt rgb24 - 2>/dev/null", tmpl);
    mv->pipe = popen(cmd, "r");
    if (!mv->pipe) {
        dw4_movie_close(mv);
        return NULL;
    }
    if (w)
        *w = mw;
    if (h)
        *h = mh;
    printf("  movie %s: %dx%d (ffmpeg rawvideo)\n", name, mw, mh);
    return mv;
}

int dw4_movie_frame(dw4_movie *mv, uint8_t *rgba)
{
    size_t px = (size_t)mv->w * (size_t)mv->h, i;
    uint8_t *raw = (uint8_t *)malloc(px * 3);

    if (!raw)
        return -1;
    if (fread(raw, 3, px, mv->pipe) != px) {
        free(raw);
        return -1;
    }
    for (i = 0; i < px; i++) {
        rgba[i * 4 + 0] = raw[i * 3 + 0];
        rgba[i * 4 + 1] = raw[i * 3 + 1];
        rgba[i * 4 + 2] = raw[i * 3 + 2];
        rgba[i * 4 + 3] = 255;
    }
    free(raw);
    return 0;
}

void dw4_movie_close(dw4_movie *mv)
{
    if (!mv)
        return;
    if (mv->pipe)
        pclose(mv->pipe);
    if (mv->tmppath[0])
        unlink(mv->tmppath);
    free(mv);
}

/* The presentation loop: decode and present until the stream ends or the user closes the window.
 * `win`/`vk` may both be NULL (decode only).  Returns 0 when frames played, 1 for none, -1 when the
 * window was closed. */
static int movie_present(dw4_movie *mv, int w, int h, dw4_window *win, dw4_vk *vk, int show_fps,
                         const char *script)
{
    struct timespec t0, tn, tp;
    int frames = 0, rc = 0;
    double fps_ema = 0.0;              /* the smoothed frame rate for the `--fps` readout */
    int mv_trace = getenv("DW4_MV_TRACE") != NULL;   /* per-frame present/gap log on stderr */
    dw4_input_state in;
    int skipped = 0;
    int started = 0, dropped = 0;
    dw4_audio *audio = NULL;
    dw4_audio_clip soundtrack = {0};
    dw4_gl_layer *overlay=NULL;
    uint8_t *rgba = (uint8_t *)malloc((size_t)w * (size_t)h * 4);

    if (!rgba)
        return 1;
    if(dw4_gpu_policy_required() && show_fps && (win || vk)){
        overlay=dw4_gl_layer_open(w,h);
        if(!overlay){dw4_gpu_policy_fail("movie overlay GPU unavailable");free(rgba);return -1;}
    }
    if (win || vk) {
        audio = dw4_audio_open();
        if (audio && dw4_audio_decode(mv->tmppath, &soundtrack) != 0) {
            fprintf(stderr, "movie: no decodable audio stream; playing video only\n");
            dw4_audio_close(audio); audio = NULL;
        }
        if (audio) {
            dw4_audio_play(audio, 0, &soundtrack, 1.0f);
            printf("  movie audio: %zu stereo frames at 48000 Hz (SDL2)\n", soundtrack.frames);
        }
    }
    dw4_input_init(&in);
    clock_gettime(CLOCK_MONOTONIC, &t0);
    tp = t0;
    for (;;) {
        dw4_fb fb;
        if (dw4_movie_frame(mv, rgba) != 0)
            break;
        if (!started) {
            clock_gettime(CLOCK_MONOTONIC, &t0); tp = t0;
            dw4_audio_resume(audio);
            started = 1;
        }
        /* the run's scripted input (when given) drives the movie too, so a scripted `cross` skips
         * the FMV exactly as the keyboard does */
        if (script)
            dw4_input_script(&in, script, frames);
        /* If decoding/presentation stalls, catch video up to the audio clock.
         * Keep reading every compressed frame, but omit stale presentations. */
        int stale = audio && dw4_audio_seconds(audio) >= (frames + 1) / 29.97;
        if (stale) dropped++;
        if ((win || vk) && !stale) {
            struct timespec a, b;
            fb.w = w;
            fb.h = h;
            fb.rgba = rgba;
            fb.z = NULL;
            if(show_fps){
                if(dw4_gpu_policy_required()){
                    if(dw4_render_fps_gpu(overlay,&fb,fps_ema)){dw4_gpu_policy_fail("movie FPS GPU draw");rc=-1;break;}
                }else dw4_render_fps(&fb,fps_ema);
            }
            clock_gettime(CLOCK_MONOTONIC, &a);
            if (vk) {
                if (dw4_vk_present(vk, &fb) < 0) {
                    dw4_gpu_policy_fail("movie Vulkan presentation");
                    rc = -1;
                    break;
                }
            } else {
                if (dw4_window_present(win, &fb) < 0) {
                    fprintf(stderr, "movie: could not present %dx%d frame\n", w, h);
                    dw4_gpu_policy_fail("movie SDL presentation");
                    rc = -1;
                    break;
                }
            }
            clock_gettime(CLOCK_MONOTONIC, &b);
            if (mv_trace)
                fprintf(stderr, "MV %d present %.2f gap %.2f\n", frames,
                        (b.tv_sec - a.tv_sec) * 1e3 + (b.tv_nsec - a.tv_nsec) / 1e6,
                        (a.tv_sec - tp.tv_sec) * 1e3 + (a.tv_nsec - tp.tv_nsec) / 1e6);
            if (vk ? !dw4_vk_pump_in(vk, &in) : !dw4_window_pump(win, &in)) {
                rc = -1;               /* the user closed the window: the caller must stop */
                break;
            }
        }
        if (stale && (win || vk) &&
            (vk ? !dw4_vk_pump_in(vk, &in) : !dw4_window_pump(win, &in))) {
            rc = -1; break;
        }
        /* The opening FMV is skippable, as it is on the console: Cross -- Space or Enter on the
         * keyboard, per the shared key map -- jumps straight on to the title. */
        if (in.cross || in.quit) {
            skipped = 1;
            break;
        }
        frames++;
        clock_gettime(CLOCK_MONOTONIC, &tn);
        {
            double want = (double)frames / 29.97;
            double got = (double)(tn.tv_sec - t0.tv_sec) + (double)(tn.tv_nsec - t0.tv_nsec) / 1e9;
            if (frames > 1 && tn.tv_sec == tp.tv_sec && tn.tv_nsec > tp.tv_nsec) {
                double inst = 1e9 / (double)(tn.tv_nsec - tp.tv_nsec);
                fps_ema = fps_ema > 0.0 ? fps_ema * 0.9 + inst * 0.1 : inst;
            }
            tp = tn;
            if (audio) got = dw4_audio_seconds(audio);
            while (want > got) {
                double delay = want - got;
                usleep((useconds_t)((delay < 0.004 ? delay : 0.004) * 1e6));
                if ((win || vk) &&
                    (vk ? !dw4_vk_pump_in(vk, &in) : !dw4_window_pump(win, &in))) {
                    rc = -1; break;
                }
                if (in.cross || in.quit) { skipped = 1; break; }
                clock_gettime(CLOCK_MONOTONIC, &tn);
                got = audio ? dw4_audio_seconds(audio) :
                    (double)(tn.tv_sec - t0.tv_sec) + (double)(tn.tv_nsec - t0.tv_nsec) / 1e9;
            }
            if (rc < 0 || skipped) break;
        }
    }
    if (audio)
        printf("  movie audio clock: %.3f s, %d stale video frame(s) omitted\n",
               dw4_audio_seconds(audio), dropped);
    dw4_audio_close(audio);
    dw4_audio_clip_free(&soundtrack);
    printf("  played %d movie frame(s) %dx%d (%.1f s)%s\n", frames, w, h, (double)frames / 29.97,
           rc < 0 ? " [window closed]" : (skipped ? " [skipped]" : ""));
    free(rgba);
    dw4_gl_layer_close(overlay);
    return rc < 0 ? -1 : (frames ? 0 : 1);
}

int dw4_movie_play_in(const char *roms_dir, const char *name, dw4_window *win, dw4_vk *vk,
                      int show_fps, const char *input_script)
{
    dw4_movie *mv;
    int w = 0, h = 0, rc;

    mv = dw4_movie_open(roms_dir, name, &w, &h);
    if (!mv)
        return 1;
    rc = movie_present(mv, w, h, win, vk, show_fps, input_script);
    dw4_movie_close(mv);
    return rc;
}

int dw4_movie_play(const char *roms_dir, const char *name, int use_window, int headless,
                   int software_reference,int show_fps, const char *input_script)
{
    dw4_movie *mv;
    dw4_window *win = NULL;
    int w = 0, h = 0, rc;
    int previous=dw4_gpu_policy_required();

    mv = dw4_movie_open(roms_dir, name, &w, &h);
    if (!mv)
        return 1;
    dw4_gpu_policy_begin(use_window && !headless && !software_reference);
    if (use_window) {
        /* Standalone movies own a window under the selected normal/reference policy. */
        win = dw4_window_open(w, h, "dw4 movie", headless);
        if (!win){
            fprintf(stderr, "movie: no window (SDL2 not compiled in, or no driver)\n");
            if(dw4_gpu_policy_required()){
                fprintf(stderr,"movie graphics: %s\n",dw4_gpu_policy_error());
                dw4_movie_close(mv);dw4_gpu_policy_begin(previous);return 1;
            }
        }
    }
    rc = movie_present(mv, w, h, win, NULL, show_fps, input_script);
    if (win)
        dw4_window_close(win);
    dw4_movie_close(mv);
    int failed=dw4_gpu_policy_error()[0]!=0;
    if(failed)fprintf(stderr,"movie graphics: %s\n",dw4_gpu_policy_error());
    if(getenv("DW4_GPU_POLICY_TRACE"))fprintf(stderr,"GPU policy CPU audit: UI %llu layer %llu mesh %llu fill %llu composite %llu\n",
        (unsigned long long)dw4_gpu_policy_cpu_count(DW4_CPU_UI),(unsigned long long)dw4_gpu_policy_cpu_count(DW4_CPU_LAYER),
        (unsigned long long)dw4_gpu_policy_cpu_count(DW4_CPU_MESH),(unsigned long long)dw4_gpu_policy_cpu_count(DW4_CPU_FILL),
        (unsigned long long)dw4_gpu_policy_cpu_count(DW4_CPU_COMPOSITE));
    dw4_gpu_policy_begin(previous);
    return failed?1:(rc < 0 ? 0 : rc); /* Closing the window remains a clean end. */
}
