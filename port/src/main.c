#define _GNU_SOURCE
/* src/main.c — the `dw4` native host executable (porting P6.1).
 *
 *   dw4 --roms <dir> --stage stag0102.igb [--ref 1] [--frames 3] [--out-dir dir]
 *
 * Boots the native engine host: platform seam, object graph, frame loop, frames to PNG.  The
 * game's own entry (`FUN_002595e0`, reached from the CRT at `0x100008`) is the same shape and is
 * what this becomes as the EE runtime is ported; see include/dw4/engine.h.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "dw4/engine.h"
#include "dw4/audio.h"
#include "dw4/frontend.h"
#include "dw4/movie.h"
#include "dw4/options.h"
#include "dw4/render.h"
#include "dw4/window.h"

static void usage(void)
{
    fprintf(stderr,
            "usage: dw4 [--roms <dir>]                    boot the game: intro FMV -> title -> play\n"
            "                                               (the asset dir is found automatically when\n"
            "                                                omitted: ./local/extracted, ../local/extracted, …;\n"
            "                                                a window; no other flag needed)\n"
            "       dw4 --roms <dir> --stage <name.igb> [--ref N] [--frames N] [--w N --h N]\n"
            "       dw4 --roms <dir> --movie <name.sfd>   play a Sofdec movie (front-end FMV)\n"
            "           [--window] [--headless] [--vulkan]  present it through the host window\n"
            "                                     (SDL2, or a Vulkan swapchain)\n"
            "       dw4 --roms <dir> --boot     boot the front-end, power-on -> title/menu\n"
            "           [--spin DEG] [--out-dir DIR] [--scene capture.tsv]\n"
            "           [--view 'm0 .. m15'|--camera [NAME]] [--fov RAD] [--aspect A]\n"
            "           [--window] [--headless] [--vulkan]  present through the host window\n"
            "                                     backend (SDL2, or a Vulkan swapchain)\n"
            "           [--input-script 'F:btn[,F:btn]']  a scripted pad for a headless run\n"
            "           [--input-script-pad N 'F:btn[,F:btn]']  the same for the pad of co-op player N (2-4) in a hub\n"
            "                                     (cross skips the opening FMV, as does Space)\n"
            "           [--frames N]              N frames, or 0 = until the window closes\n"
            "           [--w N --h N]             rendering/window resolution (default 1280x960)\n"
            "           [--fps-lock N]            the game's tick rate (default 60; 0 = display rate)\n"
            "           [--loading-min-seconds S] keep loading screens visible for at least S seconds\n"
            "           [--skip-logos]            skip startup logos for testing\n"
            "           [--mute]                  silence audio while preserving playback timing\n"
            "           [--portable]              config in userdata/config beside the executable\n"
            "           [--gl]                    draw with the GPU backend (EGL/GLES)\n"
            "           [--software]              use CPU rendering; windowed title, menus and lobby use GPU by default\n"
            "           [--texture NAME --texentry N]  sample a texture pack image (GL path)\n"
            "           [--ambient R,G,B] [--light SPEC] [--lights FILE]  the light rig\n"
            "           [--fog 'linear|exp|exp2,start,end,density,R,G,B']  the VU1 FOG rig\n");
}

/* The directory holding this executable (so the defaults resolve from any working directory). */
static char g_exedir[4096];

static void find_exe_dir(char *out, size_t cap)
{
    ssize_t n = readlink("/proc/self/exe", out, cap - 1);
    char *slash;
    if (n <= 0) {
        out[0] = 0;
        return;
    }
    out[n] = 0;
    slash = strrchr(out, '/');
    if (slash)
        *slash = 0;                               /* drop the file name */
}

/* The DW4 asset root (the directory holding NDMW.AFS / NDMW.IGB) as a working tree keeps it, so
 * `dw4` with no `--roms` still runs the game. */
static int path_ok(const char *dir, const char *name)
{
    char p[4096];
    int n = snprintf(p, sizeof(p), "%s/%s", dir, name);
    if (n < 0 || n >= (int)sizeof(p))
        return 0;
    return access(p, R_OK) == 0;
}

static const char *default_roms(void)
{
    static char beside[4096], up[4096], workspace[4096], up_roms[4096];
    const char *cand[10];
    int i, k = 0;
    if (g_exedir[0]) {                            /* beside the repo: <root>/port/build/dw4 */
        snprintf(beside, sizeof(beside), "%s/../local/extracted", g_exedir);
        snprintf(up, sizeof(up), "%s/../../local/extracted", g_exedir);
        snprintf(workspace, sizeof(workspace), "%s/../../../local/extracted", g_exedir);
        snprintf(up_roms, sizeof(up_roms), "%s/../../roms/dw4", g_exedir);
        cand[k++] = beside;
        cand[k++] = up;
        cand[k++] = workspace;
        cand[k++] = up_roms;
    }
    cand[k++] = "local/extracted";
    cand[k++] = "../local/extracted";
    cand[k++] = "../../local/extracted";
    cand[k++] = "roms/dw4";
    cand[k++] = "roms";
    cand[k] = NULL;
    for (i = 0; cand[i]; i++)
        if (path_ok(cand[i], "NDMW.AFS"))
            return cand[i];
    return NULL;
}

int main(int argc, char **argv)
{
    dw4_engine_opts o;
    dw4_created_player player = {0};
    float view[16];
    float ambient[3];
    dw4_light lights[DW4_MAX_LIGHTS];
    dw4_fog fog;
    int nlights = 0;
    int boot = 0;
    int frames_given = 0;
    int portable = 0;
    const char *movie = NULL;
    const char *input_script = NULL;

    memset(view, 0, sizeof(view));
    memset(&o, 0, sizeof(o));
    o.created_player = &player;
    find_exe_dir(g_exedir, sizeof(g_exedir));
    o.ref = 1;
    o.frames = 3;
    o.w = 1280;
    o.h = 960;
    o.spin = 8.0f;
    o.fps = -1;                 /* the frame-rate readout: on only when a window presents */
    o.fps_lock = 60;            /* the game's own tick rate (a 165 Hz display must not change it) */
    o.out_dir = ".";

    for (int a = 1; a < argc; a++) {
        if (strcmp(argv[a], "--roms") == 0 && a + 1 < argc)
            o.roms = argv[++a];
        else if (strcmp(argv[a], "--stage") == 0 && a + 1 < argc)
            o.stage = argv[++a];
        else if (strcmp(argv[a], "--ref") == 0 && a + 1 < argc)
            o.ref = (uint32_t)strtoul(argv[++a], NULL, 0);
        else if (strcmp(argv[a], "--frames") == 0 && a + 1 < argc)
            o.frames = atoi(argv[++a]), frames_given = 1;
        else if (strcmp(argv[a], "--w") == 0 && a + 1 < argc)
            o.w = atoi(argv[++a]);
        else if (strcmp(argv[a], "--h") == 0 && a + 1 < argc)
            o.h = atoi(argv[++a]);
        else if (strcmp(argv[a], "--spin") == 0 && a + 1 < argc)
            o.spin = (float)atof(argv[++a]);
        else if (strcmp(argv[a], "--out-dir") == 0 && a + 1 < argc)
            o.out_dir = argv[++a];
        else if (strcmp(argv[a], "--scene") == 0 && a + 1 < argc)
            o.scene_tsv = argv[++a];
        else if (strcmp(argv[a], "--view") == 0 && a + 1 < argc) {
            char *v = argv[++a];
            for (int k = 0; k < 16; k++)
                view[k] = (float)strtod(v, &v);
            o.view = view;
        } else if (strcmp(argv[a], "--gl") == 0)
            o.gl = 1;
        else if (strcmp(argv[a], "--software") == 0)
            o.software = 1;
        else if (strcmp(argv[a], "--texture") == 0 && a + 1 < argc)
            o.texname = argv[++a];
        else if (strcmp(argv[a], "--texentry") == 0 && a + 1 < argc)
            o.texentry = (uint32_t)strtoul(argv[++a], NULL, 0);
        else if (strcmp(argv[a], "--ambient") == 0 && a + 1 < argc) {
            if (sscanf(argv[++a], "%f,%f,%f", &ambient[0], &ambient[1], &ambient[2]) == 3)
                o.ambient = ambient;
            else
                fprintf(stderr, "dw4: --ambient wants R,G,B\n");
        } else if (strcmp(argv[a], "--light") == 0 && a + 1 < argc) {
            if (nlights < DW4_MAX_LIGHTS && dw4_render_parse_light(argv[++a], &lights[nlights]) == 0)
                nlights++;
            else
                fprintf(stderr, "dw4: bad --light spec\n");
            o.lights = lights;
            o.nlights = nlights;
        } else if (strcmp(argv[a], "--lights") == 0 && a + 1 < argc) {
            int n = dw4_render_load_lights(argv[++a], lights, DW4_MAX_LIGHTS);
            if (n < 0) {
                fprintf(stderr, "dw4: cannot read the lights file\n");
                return 1;
            }
            nlights = n;
            o.lights = lights;
            o.nlights = nlights;
        } else if (strcmp(argv[a], "--fog") == 0 && a + 1 < argc) {
            if (dw4_render_parse_fog(argv[++a], &fog) == 0)
                o.fog = &fog;
            else
                fprintf(stderr, "dw4: bad --fog spec\n");
        }
        else if (strcmp(argv[a], "--window") == 0)
            o.window = 1;
        else if (strcmp(argv[a], "--vulkan") == 0) {
            o.window = 1;
            o.vulkan = 1;            /* present through a Vulkan swapchain, not SDL's renderer */
        } else if (strcmp(argv[a], "--headless") == 0) {
            o.window = 1;
            o.headless = 1;
        } else if (strcmp(argv[a], "--fps") == 0)
            o.fps = 1;
        else if (strcmp(argv[a], "--no-fps") == 0)
            o.fps = 0;
        else if (strcmp(argv[a], "--mute") == 0)
            dw4_audio_set_muted(1);
        else if (strcmp(argv[a], "--portable") == 0)
            portable = 1;
        else if (strcmp(argv[a], "--fps-lock") == 0 && a + 1 < argc)
            o.fps_lock = atoi(argv[++a]);   /* the game's tick rate; 0 = display rate */
        else if (strcmp(argv[a], "--camera") == 0) {
            o.use_camera = 1;
            if (a + 1 < argc && argv[a + 1][0] != '-')
                o.camera = argv[++a];
        } else if (strcmp(argv[a], "--fov") == 0 && a + 1 < argc)
            o.fov = (float)atof(argv[++a]);
        else if (strcmp(argv[a], "--aspect") == 0 && a + 1 < argc)
            o.aspect = (float)atof(argv[++a]);
        else if (strcmp(argv[a], "--boot") == 0 || strcmp(argv[a], "--frontend") == 0)
            boot = 1;
        else if (strcmp(argv[a], "--loading-min-seconds") == 0 && a + 1 < argc) {
            char *end;
            const char *value = argv[++a];
            errno = 0;
            o.loading_min_seconds = strtod(value, &end);
            if (end == value || *end || errno || !isfinite(o.loading_min_seconds) ||
                o.loading_min_seconds < 0 || o.loading_min_seconds > 86400) {
                fprintf(stderr, "dw4: --loading-min-seconds requires seconds between 0 and 86400\n");
                return 2;
            }
        }
        else if (strcmp(argv[a], "--skip-logos") == 0)
            o.skip_logos = 1;
        else if (strcmp(argv[a], "--input-script") == 0 && a + 1 < argc)
            input_script = argv[++a];
        else if (strcmp(argv[a], "--input-script-pad") == 0 && a + 2 < argc && argv[a + 1][0] >= '2' && argv[a + 1][0] <= '4' && !argv[a + 1][1]) {
            o.pad_script[argv[a + 1][0] - '2'] = argv[a + 2];
            a += 2;
        }
        else if (strcmp(argv[a], "--movie") == 0 && a + 1 < argc)
            movie = argv[++a];
        else if (strcmp(argv[a], "-h") == 0 || strcmp(argv[a], "--help") == 0) {
            usage();
            return 0;
        } else {
            fprintf(stderr, "dw4: unknown argument %s\n", argv[a]);
            usage();
            return 2;
        }
    }
    /* `dw4` with no flags should just run the game: resolve the asset root from the conventional
     * places a working tree keeps it.  Overridable with --roms (or nothing else to name). */
    if (!o.roms) {
        const char *r = default_roms();
        if (r) {
            o.roms = r;
            printf("roms: %s (default; pass --roms to choose another)\n", r);
        }
    }

    /* `dw4 --roms <dir>` with nothing else boots the front-end, exactly as the operator runs it:
     * power-on -> opening -> title -> (on Game Start) the world, with no analysis-tool flag. */
    if (!o.stage && !movie)
        boot = 1;
    if (boot && !o.window && !o.headless)
        o.window = 1;               /* boot presents a window by default */
    if (movie) {
        if (!o.roms) {
            usage();
            return 2;
        }
        return dw4_movie_play(o.roms, movie, o.window, o.headless,o.software, o.fps, input_script);
    }
    if (boot) {
        char stage[128] = { 0 };
        int rc;
        if (!o.roms) {
            usage();
            return 2;
        }
        if (!frames_given)
            o.frames = (o.window && !o.headless) ? 0 : 8;   /* 0 = until the window closes */
        while (dw4_options_init(portable) < 0) {
            if (o.headless || !dw4_window_retry("Cannot load configuration", dw4_options_path()))
                return 1;
        }
        printf("config: %s\n", dw4_options_path());
        rc = dw4_engine_boot(&o, input_script, stage, sizeof(stage));
        if (rc < 0)
            return 1;
        if (rc == 1 && stage[0]) {
            /* the player chose Game Start: the port's own stage path enters the world */
            printf("  entering the first playable stage: %s\n", stage);
            o.stage = stage;
            o.frames = (o.window && !o.headless) ? 0 : 1;   /* 0 = run until the window closes */
            return dw4_engine_run(&o);
        }
        return 0;
    }
    if (!o.roms || !o.stage) {
        usage();
        return 2;
    }
    return dw4_engine_run(&o);
}
