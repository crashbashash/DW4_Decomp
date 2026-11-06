/* dw4/engine.h — the native host runtime (porting P2.1/P2.6/P6.1).
 *
 * The port has been a set of asset readers; this is the **engine host**: a `main` that boots, loads
 * a stage, constructs its object graph through the reflection object model, and then runs a frame
 * loop -- the layer the plan says is the difference between a set of loaders and a running engine
 * (`port/docs/project/tasks.md` P2.6: "without it there is no `main` to speak of").
 *
 * The engine's *own* boot lives in the EE binary: the CRT entry (`0x100008`) calls
 * `FUN_002595e0` (the game's `main`), which builds the app, creates the managers and enters the
 * frame loop in `FUN_0025a580`/`FUN_0025a8c0`.  That code is not decompiled yet, so this host runs
 * the parts that are real now -- the object model, the ported `igObject_InitHeader` engine function,
 * and the renderer -- over the same loaded data, in the same init/update/present shape.  Engine
 * functions are ported into `dw4_engine_frame` as their decompilation lands.
 */
#ifndef DW4_ENGINE_H
#define DW4_ENGINE_H

#include <stddef.h>
#include <stdint.h>

#include "dw4/render.h"       /* dw4_light: the caller's rig */

/* Session-owned creation result; save-file serialization and player spawning are separate. */
typedef struct {
    int valid, species;
    char name[9];
} dw4_created_player;

typedef struct {
    dw4_created_player *created_player; /* optional output, retained by caller across stage load */
    const char *roms;       /* the asset root (holds NDMW.AFS / NDMW.IGB) */
    const char *stage;      /* the stage file, e.g. `stag0102.igb` */
    uint32_t ref;           /* which `[pt.entry]` pack of the stage to load */
    int frames;             /* how many frames to run */
    int w, h;               /* framebuffer */
    float spin;             /* degrees the camera turns per frame */
    const char *out_dir;    /* where frame_NNNN.png goes ("." when NULL) */
    const char *scene_tsv;  /* optional live capture placing the meshes */
    const float *view;      /* optional 16-float view matrix (the engine camera); NULL = bbox fit */
    float fov, aspect;      /* the projection when `view` is given */
    int use_camera;         /* derive the view from the loaded pack's own camera */
    const char *camera;     /* camera node name, or NULL for the stage camera */
    int window;             /* present each frame through the host window backend (SDL2) */
    int vulkan;             /* with `window`: present through a Vulkan swapchain instead */
    int headless;           /* with `window`, use the SDL dummy video driver (no visible window) */
    int fps;                /* the frame-rate readout on the presented frame: -1 = only when a
                             * window is presenting, 0 = off, 1 = always (`--fps` / `--no-fps`) */
    int fps_lock;           /* the game's own tick rate: the loop is paced to this many frames a
                             * second when a window presents (60 = the PS2 game's rate); 0 = unlocked
                             * (`--fps-lock N`).  A 165 Hz display would otherwise run the loop — and
                             * the frame counter it ticks — at 165. */
    int gl;                 /* draw with the GPU backend (EGL/GLES) instead of the software one */
    double loading_min_seconds; /* testing: minimum wall-clock loading-screen duration; 0 = none */
    int skip_logos;         /* testing: skip startup logo cards */
    const char *pad_script[3]; /* testing: scripted pads of co-op players 2-4 for a hub run (as `input_script`; `--input-script-pad N`) */
    int software;           /* explicitly retain CPU rendering (including title trails) */
    /* The light rig: the model is the game's, the values are runtime-only, so
     * they are a caller input.  All NULL uses the built-in placeholder one-directional rig. */
    const float *ambient;   /* 3 floats, the ambient floor */
    const dw4_light *lights;
    int nlights;
    const dw4_fog *fog;     /* the VU1 FOG family rig, or NULL for no fog */
    /* A decoded texture pack image to sample on the GL path (the mesh -> texture binding is a
     * load-time assignment, #485, so the caller names one). */
    const char *texname;
    uint32_t texentry;      /* texture pack entry; 0 means the default 625 */
} dw4_engine_opts;

/* Boot, load, run `frames`, shut down.  Returns 0 on success. */
int dw4_engine_run(const dw4_engine_opts *o);

/* The front-end boot: power-on -> logos -> opening FMV -> the title, then **stop** and present the
 * title menu (the stagML11 backdrop + the game's own font) until input.  `input_script` is a
 * scripted pad for a headless run (NULL for a live window).  Returns 1 when the player chose Game
 * Start (the Game Start branch runs and `stage_out` holds the hand-off stage), 0 when they stopped
 * at the title, or -1 on error.  Requires `o->roms`; `o->window` presents through the host window,
 * otherwise frames are written to `o->out_dir`. */
int dw4_engine_boot(const dw4_engine_opts *o, const char *input_script,
                    char *stage_out, size_t stage_cap);

#endif /* DW4_ENGINE_H */
