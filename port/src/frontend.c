#define _DEFAULT_SOURCE
/* dw4/frontend.c — the native front-end boot (porting §4).
 *
 * Two halves, both in this file:
 *
 *   1. the `be:` API subset the front-end scripts use (an SD table + flags/counters + system
 *      values), so the recovered calls have somewhere to land;
 *   2. the stage sequencer: load each front-end script entry from `NDMW.AFS`, scan its own bytes
 *      into Lua 4.0.1, execute shared definitions, retain the bounded directive/scene adapters,
 *      resolve its scene-stage
 *      pack, and hand the title's menu to the caller.
 *
 * The plan order is the recovered one; the per-entry `expect` token makes the order
 * self-checking against the disc, so a mis-ordered or changed disc is reported, not glossed over.
 */
#include "dw4/frontend.h"
#include "dw4/gpupolicy.h"
#include "dw4/script.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dw4/igfile.h"
#include "dw4/igb.h"
#include "dw4/mount.h"
#include "dw4/movie.h"
#include "dw4/frontui.h"
#include "dw4/window.h"
#include "dw4/vk_present.h"
#include <time.h>
#include <unistd.h>

/* SLUS startup action data: OPEN waits 15 ticks; WAIT fades IN 30,
 * holds 150, fades OUT 30. Rating WAIT repeats at JOINTSET 10 and 20
 * with a 30-tick hidden gap. See boot-contract.md for asset provenance. */
static int present_boot_cards(dw4_mount *mnt, dw4_window *win, dw4_vk *vk)
{
    dw4_frontui *bandai = dw4_frontui_open_card(mnt, 1, 600, "j_bandailogo");
    dw4_frontui *rating = dw4_frontui_open_card(mnt, 0, 802, "j_rating");
    dw4_fb fb = {0};
    dw4_input_state in;
    struct timespec start, now;
    int rc = 0;
    if (!bandai || !rating || dw4_fb_init(&fb, 640, 448)) {
        fprintf(stderr, "boot cards: original models unavailable\n");
        rc = 1; goto done;
    }
    if(dw4_gpu_policy_required() && (!dw4_frontui_enable_gpu(bandai,640,448) ||
                                     !dw4_frontui_enable_gpu(rating,640,448))){
        dw4_gpu_policy_fail("startup card GPU unavailable");rc=-1;goto done;
    }
    dw4_input_init(&in);
    clock_gettime(CLOCK_MONOTONIC, &start);
    printf("      boot cards: Bandai -> Intrinsic Alchemy -> Sofdec/ADX -> opening FMV\n");
    for (int frame = 0; frame < 720; ++frame) {
        int local = frame, joint = 0, alpha = 0;
        dw4_frontui *card = bandai;
        if (frame >= 240) {
            card = rating; local = frame - 240; joint = 10;
            if (local >= 255) { local -= 255; joint = 20; }
        }
        /* OPEN and CLOSE hide the model; each visible window lasts 210 ticks. */
        int t = local - ((card == rating && joint == 20) ? 0 : 15);
        if (t >= 0 && t < 30) alpha = 128 * t / 30;
        else if (t >= 30 && t < 180) alpha = 128;
        else if (t >= 180 && t < 210) alpha = 128 * (210 - t) / 30;
        dw4_frontui_card_sample(card, joint, alpha);
        if(dw4_frontui_clear(card,&fb,0,0,0)){rc=-1;break;}
        dw4_frontui_draw(card, &fb, -1);
        if(dw4_gpu_policy_error()[0]){rc=-1;break;}
        if ((vk ? dw4_vk_present(vk, &fb) : dw4_window_present(win, &fb)) < 0) {
            rc = -1; break;
        }
        for (;;) {
            if (!(vk ? dw4_vk_pump_in(vk, &in) : dw4_window_pump(win, &in))) {
                rc = -1; break;
            }
            clock_gettime(CLOCK_MONOTONIC, &now);
            double elapsed = now.tv_sec - start.tv_sec + (now.tv_nsec - start.tv_nsec) / 1e9;
            if (elapsed >= (frame + 1) / 60.0) break;
            usleep(1000);
        }
        if (rc < 0) break;
    }
done:
    dw4_fb_free(&fb);
    dw4_frontui_close(rating); dw4_frontui_close(bandai);
    return rc;
}


/* ------------------------------------------------------------------ be: API subset ------------- */

void dw4_be_init(dw4_be_state *be) {
    memset(be, 0, sizeof(*be));
    dw4_random_init(&be->random);
    for (int i = 0; i < DW4_BE_MAX_FLAGS; i++) be->flag[i] = -1;
    be->area = -1;          /* power-on / front-end: no in-world area yet (SYSgetArea) */
    be->difficulty = 0;
    be->difficult_max = 1;
}

static dw4_be_sdrec *sd_slot(dw4_be_state *be, const char *cat, const char *name, int32_t id,
                          const char *key) {
    for (int i = 0; i < be->nsd; i++) {
        dw4_be_sdrec *s = &be->sd[i];
        if (s->id == id && strcmp(s->cat, cat) == 0 && strcmp(s->key, key) == 0 &&
            ((name == NULL && s->name[0] == 0) || (name && strcmp(s->name, name) == 0)))
            return s;
    }
    if (be->nsd >= DW4_BE_MAX_SD) return NULL;
    dw4_be_sdrec *s = &be->sd[be->nsd++];
    memset(s, 0, sizeof(*s));
    snprintf(s->cat, sizeof(s->cat), "%s", cat ? cat : "");
    snprintf(s->name, sizeof(s->name), "%s", name ? name : "");
    snprintf(s->key, sizeof(s->key), "%s", key ? key : "");
    s->id = id;
    return s;
}

static int sd_put(dw4_be_state *be, const char *cat, const char *name, int32_t id,
                  const char *key, const char *value) {
    dw4_be_sdrec *s = sd_slot(be, cat, name, id, key);
    if (!s) return -1;
    s->is_str = 1;
    snprintf(s->sval, sizeof(s->sval), "%s", value ? value : "");
    s->ival = 0;
    /* the two keys the front-end gates on have engine-side effects the sequencer models */
    if (strcmp(key, "PADINPUT") == 0) {
        be->padinput_on = (value && strcmp(value, "ENABLE") == 0);
        be->padinput_mode = be->padinput_on ? 29 : 0;
    }
    return 0;
}

static int sd_put_i(dw4_be_state *be, const char *cat, const char *name, int32_t id,
                    const char *key, int32_t value) {
    dw4_be_sdrec *s = sd_slot(be, cat, name, id, key);
    if (!s) return -1;
    s->is_str = 0;
    s->ival = value;
    s->sval[0] = 0;
    return 0;
}

int dw4_be_sd(dw4_be_state *be, const char *cat, const char *name, int32_t id,
              const char *key, const char *value) {
    sd_put(be, cat, name, id, key, value);
    return dw4_be_dm_run(be);
}

int dw4_be_sd_i(dw4_be_state *be, const char *cat, const char *name, int32_t id,
                const char *key, int32_t value) {
    sd_put_i(be, cat, name, id, key, value);
    return dw4_be_dm_run(be);
}

int dw4_be_dm_set_sd(dw4_be_state *be, const char *cat, const char *name, int32_t id,
                     const char *key, const char *value) {
    return sd_put(be, cat, name, id, key, value);
}

int dw4_be_dm_run(dw4_be_state *be) {
    be->runs++;
    /* Every queued record is "applied" the moment it is drained; its engine-side effect was taken
     * when it was set (PADINPUT above), which is the observable part for the front-end slice. */
    return be->nsd;
}

int dw4_be_dm_chk_sd(const dw4_be_state *be, const char *cat, const char *name, int32_t id,
                     const char *key, const char *op) {
    int v = 0;
    (void)name;
    for (int i = 0; i < be->nsd; i++) {
        const dw4_be_sdrec *s = &be->sd[i];
        if (s->id == id && strcmp(s->cat, cat) == 0 && strcmp(s->key, key) == 0) {
            v = s->is_str ? (s->sval[0] ? 1 : 0) : s->ival;
            break;
        }
    }
    if (op && strstr(op, "!=")) return v != 0;
    if (op && strstr(op, "==")) return v == 0;
    return v != 0;
}

void dw4_be_flag_set(dw4_be_state *be, int32_t id, int32_t v) {
    if (id < 0 || id >= DW4_BE_MAX_FLAGS) return;
    be->flag[id] = (int8_t)(v ? 1 : 0);
}

int dw4_be_flag_on(const dw4_be_state *be, int32_t id) {
    if (id < 0 || id >= DW4_BE_MAX_FLAGS) return 0;
    return be->flag[id] > 0;
}

void dw4_be_counter_set(dw4_be_state *be, int32_t id, int32_t v) {
    if (id < 0 || id >= DW4_BE_MAX_COUNTERS) return;
    be->counter[id] = v;
}

int32_t dw4_be_sys_get_area(const dw4_be_state *be) { return be->area; }
int32_t dw4_be_sys_get_difficulty(const dw4_be_state *be) { return be->difficulty; }

void dw4_be_sys_ctl_flag_folder(dw4_be_state *be, const char *cmd, int32_t id) {
    (void)cmd;
    if (id < 0 || id >= DW4_BE_MAX_FLAGS) return;
    be->flag[id] = -1;      /* CLR: drop the folder's cached flag */
}

void dw4_be_lis_set_difficult_max(dw4_be_state *be, int32_t v) { be->difficult_max = v; }
void dw4_be_cfl_clear(dw4_be_state *be) { be->cfl_clear_count++; }
void dw4_be_msgbox(dw4_be_state *be, const char *msg) { (void)msg; be->msgbox_count++; }

/* ------------------------------------------------------------------ directive scan ------------- */

static int ascii_token(const uint8_t *b, size_t n, size_t at, char *out, size_t cap) {
    size_t i = at;
    while (i < n && !((b[i] >= 'A' && b[i] <= 'Z') || (b[i] >= 'a' && b[i] <= 'z') ||
                      (b[i] >= '0' && b[i] <= '9'))) i++;
    size_t s = i;
    while (i < n && ((b[i] >= 'A' && b[i] <= 'Z') || (b[i] >= 'a' && b[i] <= 'z') ||
                     (b[i] >= '0' && b[i] <= '9') || b[i] == '_')) i++;
    size_t len = i - s;
    if (len == 0 || len >= cap) return -1;
    memcpy(out, b + s, len);
    out[len] = 0;
    return len;
}

/* A scene stage name: `stag` + a [A-Za-z0-9] run (stagis09, stagis10, stagML11, stag0001). */
static int is_stage_token(const char *t) {
    return strncasecmp(t, "stag", 4) == 0 && strlen(t) > 5;
}

/* The scripts name the scene stage `stagML11`; the manifest stores it `stagml11.igb`. */
static void tolower_name(char *dst, size_t cap, const char *src) {
    size_t i = 0;
    for (; src[i] && i + 1 < cap; i++) dst[i] = (char)tolower((unsigned char)src[i]);
    dst[i] = 0;
}

static long dw4_fe_find(const uint8_t *b, size_t n, const char *tok, size_t from) {
    size_t tl = strlen(tok);
    if (from > n || tl == 0) return -1;
    for (size_t i = from; i + tl <= n; i++)
        if (memcmp(b + i, tok, tl) == 0) return (long)i;
    return -1;
}

int dw4_frontend_scan(const uint8_t *b, size_t n, dw4_frontend_directives *out) {
    memset(out, 0, sizeof(*out));

    size_t at = 0;
    for (;;) {
        long p = dw4_fe_find(b, n, "NEXTSTAGE", at);
        if (p < 0) break;
        at = (size_t)p + 9;
        /* the first token after NEXTSTAGE that reads as a stage name; the decoy chunks
         * (`ATEPOS…NEXTSTAGE…ONCTRL`) yield a non-`stag` token and are skipped */
        for (int k = 0; k < 4; k++) {
            char tok[32];
            int len = ascii_token(b, n, at, tok, sizeof(tok));
            if (len < 0) break;
            at += (size_t)len;   /* advance past this token */
            if (is_stage_token(tok)) {
                if (!out->next_stage[0]) snprintf(out->next_stage, sizeof(out->next_stage), "%s", tok);
                int seen = 0;
                for (int j = 0; j < out->n_next; j++)
                    if (strcmp(out->all_next[j], tok) == 0) seen = 1;
                if (!seen && out->n_next < 4)
                    snprintf(out->all_next[out->n_next++], sizeof(out->all_next[0]), "%s", tok);
                break;
            }
        }
    }

    long p = dw4_fe_find(b, n, "PADINPUT", 0);
    if (p >= 0) {
        char tok[64];
        if (ascii_token(b, n, (size_t)p + 8, tok, sizeof(tok)) > 0) {
            out->has_padinput = 1;
            out->padinput_on = (strcmp(tok, "ENABLE") == 0);
        }
    }

    /* TITLE2 ... RUN: `AM_TITLE2` also contains `TITLE2`, so walk every occurrence and take the
     * first whose RUN follows within the chunk (the real `TITLE2\0\x04\0\0\0RUN`). */
    size_t ta = 0;
    for (;;) {
        long p = dw4_fe_find(b, n, "TITLE2", ta);
        if (p < 0) break;
        long end = ((long)n < p + 24) ? (long)n : p + 24;
        if (dw4_fe_find(b, (size_t)end, "RUN", (size_t)(p + 6)) >= 0) {
            out->title2_run = 1;
            break;
        }
        ta = (size_t)p + 6;
    }
    return 0;
}

/* ------------------------------------------------------------------ the recovered plan -------- */

const char *dw4_frontend_first_stage(void) {
    /* Terminal Area: model pack 820's flag-500 first-arrival branch,
     * camsp0101 and TALKFONT02 39..53. ML02 is the commander room. */
    return "stagml11.igb";
}

const char *dw4_frontend_movie(void) {
    /* The `opening` stage's Sofdec stream on the US disc (`AREA.AFS`).  MPEG-1 + ADX, 64 s:
     * . */
    return "aus_opening.sfd";
}

int dw4_frontend_stages(dw4_frontend_stage *out, int cap) {
    static const dw4_frontend_stage plan[] = {
        /* the boot/attract chain */
        {800, "menu-database",      "",         "stagML11", 0},
        {802, "bandai-logo",        "stagis09", "stagis09", 0},
        {804, "opening",            "stagis10", "stagis10", 0},
        {806, "title-screen",       "stagML11", "stagML11", 0},
        /* the Game Start branch: character-select (new game).  The live run enters at 808 and, on
         * a created Digimon, hands off to the Terminal Area (stagML11); 810/812 are the sibling
         * character-select entries. */
        {808, "character-select-1", "stagis11", "stagML11", 1},
        {810, "character-select-2", "stagis12", "stagML11", 1},
        {812, "character-select-3", "stagis13", "stagML11", 1},
    };
    int n = (int)(sizeof(plan) / sizeof(plan[0]));
    if (n > cap) n = cap;
    for (int i = 0; i < n; i++) out[i] = plan[i];
    return n;
}

/* ------------------------------------------------------------------ entry chunk names ---------- */

/* Fallback for a pack whose Lua records do not tile in one chain: read the chunk names straight
 * off the bytes (the `*.lua` tokens, which is how the reference extractor found them). */
static int scan_lua_names(const uint8_t *b, size_t n, char names[][48], int cap) {
    int cnt = 0;
    for (size_t i = 0; i + 4 <= n; i++) {
        if (memcmp(b + i, ".lua", 4) != 0) continue;
        size_t e = i + 4, s = i;
        while (s > 0 && (isalnum((unsigned char)b[s - 1]) || b[s - 1] == '_' || b[s - 1] == '.')) s--;
        size_t len = e - s;
        if (len < 5 || len >= 48) continue;
        char t[48];
        memcpy(t, b + s, len);
        t[len] = 0;
        int dup = 0;
        for (int k = 0; k < cnt; k++) if (strcmp(names[k], t) == 0) dup = 1;
        if (!dup && cnt < cap) snprintf(names[cnt++], 48, "%s", t);
    }
    return cnt;
}

static int collect_chunks(const dw4_igb *g, const uint8_t *blob, size_t len,
                          char names[][48], int cap) {
    int n = 0;
    uint32_t chain = dw4_igb_find_chain(g, 0x800);
    enum { NREC = 512 };
    dw4_igb_record *recs = calloc(NREC, sizeof(*recs));
    if (!recs) return 0;
    uint32_t got = dw4_igb_chain(g, chain, recs, NREC);
    uint32_t nfill = got < NREC ? got : NREC;   /* the chain tiles past the array; only NREC filled */
    for (uint32_t i = 0; i < nfill && n < cap; i++) {
        dw4_igb_record *r = &recs[i];
        if (!r->class_name || strcmp(r->class_name, "beLuaData") != 0) continue;
        if (r->name && r->name[0]) snprintf(names[n++], 48, "%s", r->name);
    }
    for (uint32_t i = 0; i < nfill; i++) dw4_igb_record_free(&recs[i]);
    free(recs);
    if (n == 0) n = scan_lua_names(blob, len, names, cap);
    return n;
}

/* ------------------------------------------------------------------ the sequencer --------------- */

static void install_title_menu(dw4_title_menu *m) {
    memset(m, 0, sizeof(*m));
    snprintf(m->row[0].label, sizeof(m->row[0].label), "Game Start");
    snprintf(m->row[1].label, sizeof(m->row[1].label), "Option");
    m->nrow = 2;
    m->sel = 0;
    m->running = 1;
}

static int run_frontend(const char *roms, dw4_title_menu *menu, char *stage_out, size_t stage_cap,
                        int present_movie, int show_fps, int game_branch, int handoff, int attract,
                        struct dw4_window *win, struct dw4_vk *vk, const char *input_script, int skip_logos) {
    dw4_mount mnt;
    char afs[4096];
    dw4_frontend_stage stages[DW4_FE_MAX_STAGES];
    int ns, rc = 0;

    memset(&mnt, 0, sizeof(mnt));
    ns = dw4_frontend_stages(stages, DW4_FE_MAX_STAGES);
    snprintf(afs, sizeof(afs), "%s/NDMW.AFS", roms);

    printf("dw4 front-end boot: blank slate -> %d stage(s)\n", ns);
    if (dw4_mount_open(&mnt, roms) != 0) {
        fprintf(stderr, "  front-end: cannot mount assets at %s\n", roms);
        return -1;
    }

    dw4_be_state be;
    dw4_be_init(&be);
    dw4_be_cfl_clear(&be);      /* the boot camera reset */

    dw4_script *scripts = dw4_script_open(NULL, NULL);
    if (!scripts) { dw4_mount_close(&mnt); return -1; }

    if (skip_logos) printf("  front-end: --skip-logos skips startup logo cards\n");

    for (int i = 0; i < ns; i++) {
        const dw4_frontend_stage *st = &stages[i];
        dw4_igfile f;
        dw4_igb g;
        char chunks[24][48];
        int nch;
        dw4_frontend_directives d;

        if (st->game != game_branch || (attract && st->entry == 800))
            continue;   /* the boot chain and the Game Start branch are run separately */

        if (skip_logos && st->entry == 802)
            continue;

        memset(&f, 0, sizeof(f));
        if (dw4_igfile_open_afs(&f, afs, st->entry) != 0) {
            fprintf(stderr, "  front-end: entry %u (%s) did not load\n", st->entry, st->tree);
            rc = -1;
            break;
        }
        const uint8_t *blob = dw4_igfile_data(&f);
        size_t len = dw4_igfile_size(&f);

        memset(&g, 0, sizeof(g));
        if (dw4_igb_open(&g, blob, len, 0) != 0) {
            fprintf(stderr, "  front-end: entry %u (%s) is not an igBinary pack\n", st->entry, st->tree);
            rc = -1;
            dw4_igfile_close(&f);
            break;
        }

        int loaded = dw4_script_remove_all(scripts) || dw4_script_recreate(scripts) ? -1 :
            dw4_script_collect_pack(scripts, &g);
        if (loaded < 0 || ((st->entry == 800 || st->entry == 806) &&
                          dw4_script_run(scripts, "func.lua"))) {
            fprintf(stderr, "front-end Lua: %s\n", dw4_script_error(scripts));
            dw4_igb_close(&g); dw4_igfile_close(&f); rc = -1; break;
        }
        printf("      Lua 4.0.1: loaded %d original named chunks\n", loaded);
        nch = collect_chunks(&g, blob, len, chunks, 24);
        dw4_frontend_scan(blob, len, &d);

        if (st->game && (i == 0 || !stages[i - 1].game))
            printf("  -- Game Start branch: character-select --\n");
        printf("  [%d] entry %u %-13s : %zu bytes, %d Lua chunk(s)\n",
               i, st->entry, st->tree, len, nch);
        printf("      chunks:");
        for (int k = 0; k < nch; k++) printf(" %s", chunks[k]);
        printf("\n");
        printf("      be: NEXTSTAGE %-9s (all:%s%s%s%s), PADINPUT %s%s%s\n",
               d.next_stage[0] ? d.next_stage : "(none)",
               d.n_next > 0 ? " " : "", d.n_next > 0 ? d.all_next[0] : "",
               d.n_next > 1 ? " " : "", d.n_next > 1 ? d.all_next[1] : "",
               d.has_padinput ? (d.padinput_on ? "ENABLE" : "DISABLE") : "(none)",
               d.title2_run ? ", TITLE2 RUN" : "", "");

        if (st->expect[0]) {
            if (strcmp(d.next_stage, st->expect) == 0)
                printf("      disc check: NEXTSTAGE == %s  ok\n", st->expect);
            else {
                printf("      disc check: FAIL (expected %s, entry carries '%s')\n",
                       st->expect, d.next_stage);
                rc = -1;
            }
        }

        if (!strcmp(st->tree, "bandai-logo") && present_movie && (win || vk)) {
            int cards = present_boot_cards(&mnt, win, vk);
            if (cards < 0) { rc = -2; break; }
            if (cards > 0) rc = -1;
        }

        /* The `opening` stage is the boot FMV: play its Sofdec stream through the host window when
         * the caller asked for pixels; a headless boot only reports it (so a check never blocks on
         * 64 s of video). */
        if (strcmp(st->tree, "opening") == 0) {
            if (present_movie && !getenv("DW4_SKIP_MOVIE")) {
                printf("      opening FMV: playing %s\n", dw4_frontend_movie());
                /* into the boot's own window: the FMV and the title are one window, so closing it
                 * here ends the run instead of opening a second one at the title */
                if (dw4_movie_play_in(roms, dw4_frontend_movie(), win, vk, show_fps != 0,
                                      input_script) < 0) {
                    rc = -2;                     /* the user closed the window */
                    break;
                }
            } else {
                printf("      opening FMV: %s (not played: no window)\n", dw4_frontend_movie());
            }
        }

        /* drive the be: API subset */
        dw4_be_dm_set_sd(&be, "STAGECTL", NULL, -2, "NEXTSTAGE", d.next_stage);
        dw4_be_dm_run(&be);
        if (d.has_padinput)
            dw4_be_sd(&be, "STAGECTL", NULL, -2, "PADINPUT", d.padinput_on ? "ENABLE" : "DISABLE");

        /* the scene-stage pack this entry drives */
        if (st->scene[0]) {
            dw4_ref refs[8];
            char sn[80], name_lc[64];
            tolower_name(name_lc, sizeof(name_lc), st->scene);
            snprintf(sn, sizeof(sn), "%s.igb", name_lc);
            uint32_t nr = dw4_igfile_stage_refs(&mnt, sn, refs, 8);
            printf("      scene %-9s (%s): %u pack ref(s)", st->scene, sn, nr);
            for (uint32_t r = 0; r < nr && r < 8; r++) {
                uint32_t sz = 0;
                if (dw4_mount_entry(&mnt, refs[r].pt, refs[r].entry, &sz, NULL))
                    printf("  [%d.%d]=%uB", refs[r].pt, refs[r].entry, sz);
            }
            printf("\n");
            if (nr == 0) { printf("      scene check: FAIL (no pack refs)\n"); rc = -1; }
        }

        /* the title entry runs the live menu: TITLE2 RUN + PADINPUT ENABLE 29 */
        if (strcmp(st->tree, "title-screen") == 0) {
            if (d.title2_run) {
                dw4_be_sd(&be, "SOUND", NULL, 0, "PLAY", "AM_TITLE");
                printf("      be: SYSgetArea()=%d -> PLAY \"AM_TITLE\"\n", dw4_be_sys_get_area(&be));
                printf("      be: TITLE2 RUN\n");
                printf("      be: PADINPUT ENABLE %d\n", be.padinput_mode);
                dw4_be_flag_set(&be, 81, -1);
                dw4_be_counter_set(&be, 1, -1);
                dw4_be_sys_ctl_flag_folder(&be, "CLR", 81);
                dw4_be_lis_set_difficult_max(&be, 1);
                printf("      be: FLGisOn(81)=%d COUNTERset(1) SYSctlFlagFolder(CLR) LISsetDifficultMax\n",
                       dw4_be_flag_on(&be, 81));
                if (menu) install_title_menu(menu);
                printf("  title: 'Press START button' screen (TITLE2 RUN); START -> 'Game Start' / 'Option'\n");
            } else {
                printf("      title check: FAIL (no TITLE2 RUN)\n");
                rc = -1;
            }
        }

        dw4_igb_close(&g);
        dw4_igfile_close(&f);
    }

    if (rc == 0 && handoff) {
        /* the hand-off: the Main Lobby must resolve to real packs before we call it reached */
        const char *first = dw4_frontend_first_stage();
        dw4_ref refs[8];
        uint32_t nr = dw4_igfile_stage_refs(&mnt, first, refs, 8);
        printf("  first playable stage %-12s (%s): %u pack ref(s)", "stagML11", first, nr);
        for (uint32_t r = 0; r < nr && r < 8; r++) {
            uint32_t sz = 0;
            if (dw4_mount_entry(&mnt, refs[r].pt, refs[r].entry, &sz, NULL))
                printf("  [%d.%d]=%uB", refs[r].pt, refs[r].entry, sz);
        }
        printf("\n");
        if (nr == 0) {
            printf("      hand-off check: FAIL (no pack refs for %s)\n", first);
            rc = -1;
        } else if (stage_out && stage_cap) {
            snprintf(stage_out, stage_cap, "%s", first);
        }
    }
    dw4_script_close(scripts);
    dw4_mount_close(&mnt);
    if (rc == -2)
        return -2;                           /* the window was closed during the FMV */
    if (rc == 0) {
        if (handoff)
            printf("dw4 front-end: reached the first playable stage (%s)  ok\n",
                   dw4_frontend_first_stage());
        else
            printf("dw4 front-end: stopped at the title, awaiting input  ok\n");
    }
    return rc;
}

int dw4_frontend_boot(const char *roms, dw4_title_menu *menu, char *stage_out, size_t stage_cap,
                      int present_movie, int show_fps, struct dw4_window *win, struct dw4_vk *vk,
                      const char *input_script, int skip_logos) {
    /* the boot chain only: 800 -> 802 -> 804 -> 806, stopping at the title (no hand-off).  The
     * opening FMV presents into `win`/`vk` (the boot's own window), so the front-end is one window. */
    return run_frontend(roms, menu, stage_out, stage_cap, present_movie, show_fps, 0, 0, 0, win, vk,
                        input_script, skip_logos);
}

int dw4_frontend_game_start(const char *roms, char *stage_out, size_t stage_cap, int show_fps) {
    /* the Game Start branch: character-select 808/810/812, then the hand-off to stagML11 */
    return run_frontend(roms, NULL, stage_out, stage_cap, 0, show_fps, 1, 1, 0, NULL, NULL, NULL, 0);
}

int dw4_frontend_attract(const char *roms, dw4_title_menu *menu, int present_movie,
                         int show_fps, struct dw4_window *win, struct dw4_vk *vk) {
    /* Retail requests stagIS09: reuse the host's existing 802 -> 804 -> 806 route. */
    return run_frontend(roms, menu, NULL, 0, present_movie, show_fps, 0, 0, 1, win, vk, NULL, 0);
}
