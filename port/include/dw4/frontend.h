/* dw4/frontend.h — the front-end boot: engine -> logos -> opening -> title/menu (porting §4).
 *
 * The front-end is not one function.  It is a chain of `NDMW.AFS` **stage entries** (800
 * menu-database, 802 bandai-logo -> scene `stagis09`, 804 opening -> `stagis10`, 806 title-screen
 * -> `stagML11`), each a set of Lua chunks run in order, driven by the script's own `be:` API
 * (`DMsetSD("STAGECTL", …, "NEXTSTAGE", stage, mode)` + `DMrun()`, gated by `PADINPUT ENABLE 29`).
 * See `DW4_Decomp/docs/engine/front-end-boot.md` (finding #606).
 *
 * The port now loads original chunks into Lua 4.0.1 and executes shared definitions.
 * Scene orchestration still uses a **native stage/script sequencer** with the
 * `be:` API subset the front-end uses and a hard-coded, disc-checked four-stage plan.  The plan's
 * stage directives are not taken on trust: each entry is loaded from the disc and its own bytes are
 * scanned for the `NEXTSTAGE`/`PADINPUT`/`TITLE2` tokens the Lua bytecode carries, so a disc that
 * disagrees fails verification instead of silently "working".
 */
#ifndef DW4_FRONTEND_H
#define DW4_FRONTEND_H

#include <stddef.h>
#include <stdint.h>
#include "dw4/random.h"

#define DW4_BE_MAX_SD       64
#define DW4_BE_MAX_FLAGS    1024
#define DW4_BE_MAX_COUNTERS 64
#define DW4_BE_MAX_ROWS     8
#define DW4_FE_MAX_STAGES   8

/* One queued `be:DMsetSD(<catalog>, <name>, <id>, <key>, <value>)`.  The engine keeps a small SD
 * (script-data) table; the port stores it the same way so `DMchkSD` can be answered from state. */
typedef struct {
    char    cat[24];
    char    name[48];
    int32_t id;
    char    key[24];
    int32_t ival;
    char    sval[64];
    int     is_str;
} dw4_be_sdrec;

/* The front-end's `be:` state: the SD table plus the flags, counters and system values the
 * front-end scripts touch (finding #606). */
typedef struct {
    dw4_be_sdrec sd[DW4_BE_MAX_SD];
    dw4_random random;                     /* boot stream; never reset by VM/stage changes */
    uint32_t action_rhythm;                 /* shared beAction2WAITCHECK R??S value */
    int       nsd;
    int8_t    flag[DW4_BE_MAX_FLAGS];       /* -1 unset, 0 off, 1 on */
    int32_t   counter[DW4_BE_MAX_COUNTERS];
    int32_t   area;                         /* SYSgetArea: -1 = power-on / front-end */
    int32_t   difficulty;                   /* SYSgetDifficulty */
    int32_t   difficult_max;                /* LISsetDifficultMax */
    int       padinput_on;                  /* the STAGECTL PADINPUT gate */
    int32_t   padinput_mode;                /* its argument (29 at the title) */
    int       cfl_clear_count;
    int       msgbox_count;
    int       runs;                         /* DMrun() calls that drained the queue */
} dw4_be_state;

/* --- the `be:` API subset (finding #606) -------------------------------------------------------- */
void dw4_be_init(dw4_be_state *be);

/* be:sd(cat, name, id, key, value[, arg]) — set one SD record and run it immediately. */
int  dw4_be_sd(dw4_be_state *be, const char *cat, const char *name, int32_t id,
               const char *key, const char *value);
int  dw4_be_sd_i(dw4_be_state *be, const char *cat, const char *name, int32_t id,
                 const char *key, int32_t value);

/* be:DMsetSD(...) queues; be:DMrun() drains the queue (returns the number applied). */
int  dw4_be_dm_set_sd(dw4_be_state *be, const char *cat, const char *name, int32_t id,
                      const char *key, const char *value);
int  dw4_be_dm_run(dw4_be_state *be);

/* be:DMchkSD(cat, name, id, key, op) — 1 when the queued condition holds, else 0.  `op` is Lua's
 * comparison text (`"!=0"`, `"==0"`); an unknown/absent record reads as 0. */
int  dw4_be_dm_chk_sd(const dw4_be_state *be, const char *cat, const char *name, int32_t id,
                      const char *key, const char *op);

/* be:FLGset / be:FLGisOn / be:COUNTERset */
void dw4_be_flag_set(dw4_be_state *be, int32_t id, int32_t v);
int  dw4_be_flag_on(const dw4_be_state *be, int32_t id);
void dw4_be_counter_set(dw4_be_state *be, int32_t id, int32_t v);

/* be:SYSgetArea / be:SYSgetDifficulty / be:SYSctlFlagFolder / be:LISsetDifficultMax /
 * be:CFLclear / be:MsgBox */
int32_t dw4_be_sys_get_area(const dw4_be_state *be);
int32_t dw4_be_sys_get_difficulty(const dw4_be_state *be);
void    dw4_be_sys_ctl_flag_folder(dw4_be_state *be, const char *cmd, int32_t id);
void    dw4_be_lis_set_difficult_max(dw4_be_state *be, int32_t v);
void    dw4_be_cfl_clear(dw4_be_state *be);
void    dw4_be_msgbox(dw4_be_state *be, const char *msg);

/* --- the title screen's menu (beNDMWTitle2 / beNDMWTitle2Option) -------------------------------- */
typedef struct {
    char label[32];
} dw4_title_row;

typedef struct {
    dw4_title_row row[DW4_BE_MAX_ROWS];
    int nrow;
    int sel;
    int running;
} dw4_title_menu;

/* --- the stage directives an entry carries, read without a Lua VM ------------------------------- */
typedef struct {
    char next_stage[32];    /* the first `stag*` token after a NEXTSTAGE */
    char all_next[4][32];   /* every distinct `stag*` token seen after a NEXTSTAGE */
    int  n_next;
    int  has_padinput;
    int  padinput_on;       /* PADINPUT ENABLE seen (vs DISABLE) */
    int  title2_run;        /* TITLE2 ... RUN seen (the title's live menu) */
} dw4_frontend_directives;

/* Scan an entry's raw bytes for the directives.  Lua 4.0.1 stores string constants as inline
 * ASCII, so the tokens are found without a VM.  Returns 0. */
int dw4_frontend_scan(const uint8_t *buf, size_t len, dw4_frontend_directives *out);

/* One row of the recovered front-end plan: `entry` is the AFS script entry, `tree` its name,
 * `scene` the scene-stage pack it drives (`""` when none), `expect` the `stag*` token its own
 * bytes must carry (the disc check), and `game` marks the Game Start branch (character-select)
 * rather than the boot/attract chain. */
typedef struct {
    uint32_t    entry;
    const char *tree;
    const char *scene;
    const char *expect;
    int         game;
} dw4_frontend_stage;

/* The recovered plan (finding #606): the boot/attract chain 800 -> 802 -> 804 -> 806, then the
 * Game Start branch 808 -> 810 -> 812 (character-select; scenes stagis11/12/13).  Returns the
 * count, fills up to `cap`. */
int dw4_frontend_stages(dw4_frontend_stage *out, int cap);

/* The first playable stage the front-end hands off to once a Digimon is created — the Main Lobby
 * (`stagML02`, packs 815 + 816, the Digi-Elf's `n_digilff_*` scripts), captured live after
 * character creation.  A manifest name (`stagml02.igb`), or "" if unknown. */
const char *dw4_frontend_first_stage(void);

/* The opening stage's Sofdec movie (the boot FMV).  It is the US disc's opening; the stream is
 * the seam in `dw4/movie.h`. */
const char *dw4_frontend_movie(void);

/* Boot the port from a blank slate: the boot chain and the Game Start branch, power-on ->
 * character-select, then hand off to the first playable stage.  Loads each script entry and its
 * scene-stage packs from the disc, drives the `be:` API subset, and leaves the title menu in
 * `menu` (may be NULL).  Writes the hand-off stage's manifest name into `stage_out` (may be NULL).
 * Returns 0, or -1 on a load failure.  Prints the machine-checkable trace to stdout.
 * `show_fps` draws the frame-rate readout on the presented frames (-1 = only when a window).
 * `win`/`vk` are the boot's own window (either may be NULL); the opening FMV presents into it, so
 * the whole front-end is one window.  Returns -2 when that window was closed during the FMV.
 * `input_script` is the run's frame-indexed input timeline (may be NULL); the opening FMV consumes
 * it too, so a scripted `cross` skips the movie (and a keyboard Cross/Space skips it live). */
/* skip_logos bypasses startup entry 802, keeping database/title initialization. */
struct dw4_window;
struct dw4_vk;
int dw4_frontend_attract(const char *roms, dw4_title_menu *menu, int present_movie,
                         int show_fps, struct dw4_window *win, struct dw4_vk *vk);
int dw4_frontend_boot(const char *roms, dw4_title_menu *menu, char *stage_out, size_t stage_cap,
                      int present_movie, int show_fps, struct dw4_window *win, struct dw4_vk *vk,
                      const char *input_script, int skip_logos);

/* The Game Start branch: character-select entries 808/810/812, then the hand-off check for the Main
 * Lobby (`stagML02`).  Run only after the player confirms Game Start at the title.  Returns 0, or -1
 * on a load/check failure. */
int dw4_frontend_game_start(const char *roms, char *stage_out, size_t stage_cap, int show_fps);

#endif /* DW4_FRONTEND_H */
