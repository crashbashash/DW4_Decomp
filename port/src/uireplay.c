/* src/uireplay.c — the captured-frame 2D layer replay, shared by `dw4asset` and the `dw4` host.
 *
 * Lifted out of `dw4asset.c`: one frame is a list of screen-space triangles in
 * the GS's draw order; the textures are `<texdir>/<key>.rgba`.  The host reuses it for the title's
 * captured menu layer, so the front-end presentation and the analysis tool read the same files the
 * same way.
 */
#define _GNU_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dw4/uireplay.h"

/* --- parsing ---------------------------------------------------------------------------------- */

static int namecmp(const void *a, const void *b)
{
    return strcmp((const char *)a, (const char *)b);
}

/* One `ui.tsv` vertex: `nf` floats (`x y u v`, or `x y s t q` in the `#stq` form) then 4 ints. */
static int ui_parse_vert(const char **pp, float v[5], int col[4], int nf)
{
    const char *p = *pp;
    int i;
    for (i = 0; i < nf; i++) {
        char *end;
        while (*p == ' ' || *p == '\t')
            p++;
        if (!*p || *p == '\n')
            return -1;
        v[i] = strtof(p, &end);
        if (end == p)
            return -1;
        p = end;
    }
    if (nf == 4)
        v[4] = 1.0f;
    for (i = 0; i < 4; i++) {
        char *end;
        while (*p == ' ' || *p == '\t')
            p++;
        if (!*p || *p == '\n')
            return -1;
        col[i] = (int)strtol(p, &end, 10);
        if (end == p)
            return -1;
        p = end;
    }
    *pp = p;
    return 0;
}

/* Is `name` in the comma-separated `hide` list? */
static int ui_hidden(const char *hide, const char *name)
{
    size_t nl;
    if (!hide || !*hide || !name)
        return 0;
    nl = strlen(name);
    for (;;) {
        const char *e = strchr(hide, ',');
        size_t el = e ? (size_t)(e - hide) : strlen(hide);
        if (el == nl && strncmp(hide, name, nl) == 0)
            return 1;
        if (!e)
            return 0;
        hide = e + 1;
    }
}

/* How many threads a replay uses: one per online core (the draws must stay in order, so the threads
 * split the frame's rows rather than the draws — see dw4_render_ui_draws). */
static int ui_cores(void)
{
#ifdef _SC_NPROCESSORS_ONLN
    long n = sysconf(_SC_NPROCESSORS_ONLN);
    return (n > 0 && n < 64) ? (int)n : 1;
#else
    return 1;
#endif
}

/* Textures by <texdir>/<name>.rgba, decoded once (re-reading and re-decoding for every triangle row
 * was what made a per-frame layer expensive; a frame loads each of its five textures once). */
static const dw4_tex *ui_tex_get(const char *texdir, const char *name)
{
    static struct { char key[512]; dw4_tex tex; } cache[64];
    static int n = 0;
    char key[512];
    int i;
    snprintf(key, sizeof(key), "%s/%.200s", texdir ? texdir : ".", name);
    for (i = 0; i < n; i++)
        if (strcmp(cache[i].key, key) == 0)
            return &cache[i].tex;
    if (n >= (int)(sizeof(cache) / sizeof(cache[0])))
        return NULL;
    {
        char texpath[2048];
        uint8_t hdr[8], *px;
        uint32_t tw, th;
        FILE *tf;
        snprintf(texpath, sizeof(texpath), "%s.rgba", key);
        tf = fopen(texpath, "rb");
        if (!tf || fread(hdr, 1, 8, tf) != 8) {
            if (tf)
                fclose(tf);
            return NULL;
        }
        tw = (uint32_t)hdr[0] | ((uint32_t)hdr[1] << 8) | ((uint32_t)hdr[2] << 16) |
             ((uint32_t)hdr[3] << 24);
        th = (uint32_t)hdr[4] | ((uint32_t)hdr[5] << 8) | ((uint32_t)hdr[6] << 16) |
             ((uint32_t)hdr[7] << 24);
        px = (uint8_t *)malloc((size_t)tw * th * 4);
        if (!px || fread(px, 1, (size_t)tw * th * 4, tf) != (size_t)tw * th * 4) {
            free(px);
            fclose(tf);
            return NULL;
        }
        fclose(tf);
        snprintf(cache[n].key, sizeof(cache[n].key), "%s", key);
        memset(&cache[n].tex, 0, sizeof(cache[n].tex));
        cache[n].tex.rgba = px;
        cache[n].tex.w = (int)tw;
        cache[n].tex.h = (int)th;
        return &cache[n++].tex;
    }
}

/* Parse a replay file into a dw4_ui_draw list. */
static int ui_parse_file(const char *path, const char *texdir, const char *hide, float sx, float sy,
                         dw4_ui_draw **out)
{
    FILE *fp = fopen(path, "r");
    char line[1024];
    int n = 0, cap = 0, stq = 0;
    dw4_ui_draw *list = NULL;
    uint8_t blend = 1;                          /* 0 opaque, 1 alpha (0x44), 2 additive (0x48) */
    *out = NULL;
    if (!fp)
        return -1;
    while (fgets(line, sizeof(line), fp)) {
        char name[256];
        float v[3][5];
        int col3[3][4];
        uint8_t col8[3][4];
        char *p = line;
        int k, len = 0;
        if (line[0] == '#' && strncmp(line, "#stq", 4) == 0) {
            stq = 1;                                /* the perspective-correct form */
            continue;
        }
        while (*p && *p != '\t' && *p != '\n' && len < (int)sizeof(name) - 1)
            name[len++] = *p++;
        name[len] = 0;
        if (*p != '\t')                             /* a header or a blank line */
            continue;
        p++;
        for (k = 0; k < 3; k++)
            if (ui_parse_vert((const char **)&p, v[k], col3[k], stq ? 5 : 4) != 0)
                break;
        if (k != 3)
            continue;
        {                                       /* an optional 4th field: the draw's blend code */
            const char *q = p;
            while (*q == ' ' || *q == '\t')
                q++;
            if (*q && *q != '\n') {
                long av = strtol(q, NULL, 10);
                blend = (av >= 0 && av <= 2) ? (uint8_t)av : 1;
            }
        }
        if (ui_hidden(hide, name))              /* the host draws its own interactive rows */
            continue;
        for (k = 0; k < 3; k++) {               /* compose at the caller's framebuffer size */
            v[k][0] *= sx;
            v[k][1] *= sy;
        }
        for (k = 0; k < 3; k++) {               /* one colour per vertex: a lit draw interpolates */
            col8[k][0] = (uint8_t)col3[k][0];
            col8[k][1] = (uint8_t)col3[k][1];
            col8[k][2] = (uint8_t)col3[k][2];
            col8[k][3] = (uint8_t)col3[k][3];
        }
        {
            const dw4_tex *t = NULL;
            if (strcmp(name, "-") != 0) {       /* "-" is an untextured (vertex-colour) draw */
                t = ui_tex_get(texdir, name);
                if (!t)
                    continue;
            }
            if (n == cap) {
                dw4_ui_draw *grown;
                cap = cap ? cap * 2 : 256;
                grown = (dw4_ui_draw *)realloc(list, (size_t)cap * sizeof(*list));
                if (!grown) {
                    free(list);
                    fclose(fp);
                    return -1;
                }
                list = grown;
            }
            memset(&list[n], 0, sizeof(list[n]));
            list[n].tex = t;
            list[n].blend = blend;
            list[n].stq = (uint8_t)stq;
            memcpy(list[n].v, v, sizeof(v));
            memcpy(list[n].rgba, col8, sizeof(col8));
            n++;
        }
    }
    fclose(fp);
    *out = list;
    return n;
}

/* The parsed list, kept per (path, texdir, hide): once the drawing is fast, re-reading and
 * re-parsing the file every frame is a measurable share of the frame. */
static const dw4_ui_draw *ui_draws_for(const char *path, const char *texdir, const char *hide,
                                       float sx, float sy, int *np)
{
    static struct {
        char key[1200];
        dw4_ui_draw *list;
        int n;
    } cache[64];
    static int ncache = 0;
    char key[1200];
    int i;
    *np = 0;
    snprintf(key, sizeof(key), "%s|%.400s|%.400s|%.4f,%.4f", path ? path : "",
             texdir ? texdir : "", hide ? hide : "", (double)sx, (double)sy);
    for (i = 0; i < ncache; i++)
        if (strcmp(cache[i].key, key) == 0) {
            *np = cache[i].n;
            return cache[i].list;
        }
    {
        dw4_ui_draw *list = NULL;
        int n = ui_parse_file(path, texdir, hide, sx, sy, &list);
        if (n <= 0)
            return NULL;
        if (ncache < (int)(sizeof(cache) / sizeof(cache[0]))) {
            snprintf(cache[ncache].key, sizeof(cache[ncache].key), "%s", key);
            cache[ncache].list = list;
            cache[ncache].n = n;
            ncache++;
        }
        *np = n;
        return list;
    }
}

int dw4_ui_draw_file(dw4_fb *fb, const char *path, const char *texdir, int nthreads,
                     const char *hide, float sx, float sy)
{
    const dw4_ui_draw *list;
    int n = 0;
    list = ui_draws_for(path, texdir, hide, sx, sy, &n);
    if (!list || n <= 0)
        return -1;
    dw4_render_ui_draws(fb, list, n, nthreads > 0 ? nthreads : ui_cores());
    return n;
}

/* --- a directory of frames -------------------------------------------------------------------- */

struct dw4_uiseq {
    char (*paths)[1600];
    int n;
    char *texdir;
    char *hide;
    float sx, sy;
};

dw4_uiseq *dw4_uiseq_open(const char *dir, const char *texdir, const char *hide, float sx, float sy)
{
    dw4_uiseq *q;
    DIR *d;
    struct dirent *e;
    char names[400][512];
    int m = 0;

    if (!dir)
        return NULL;
    d = opendir(dir);
    if (!d)
        return NULL;
    while ((e = readdir(d)) != NULL && m < 400) {
        size_t l = strlen(e->d_name);
        if (l > 4 && l < sizeof(names[0]) && strcmp(e->d_name + l - 4, ".tsv") == 0)
            snprintf(names[m++], sizeof(names[0]), "%s", e->d_name);
    }
    closedir(d);
    if (m == 0)
        return NULL;
    qsort(names, (size_t)m, sizeof(names[0]), namecmp);
    q = (dw4_uiseq *)calloc(1, sizeof(*q));
    if (!q)
        return NULL;
    q->paths = (char (*)[1600])calloc((size_t)m, sizeof(*q->paths));
    if (!q->paths) {
        free(q);
        return NULL;
    }
    while (q->n < m)
        snprintf(q->paths[q->n], sizeof(q->paths[0]), "%s/%s", dir, names[q->n]), q->n++;
    q->texdir = strdup(texdir ? texdir : ".");
    q->hide = strdup(hide ? hide : "");
    q->sx = sx > 0.0f ? sx : 1.0f;
    q->sy = sy > 0.0f ? sy : 1.0f;
    return q;
}

int dw4_uiseq_count(const dw4_uiseq *q)
{
    return q ? q->n : 0;
}

int dw4_uiseq_draw(dw4_uiseq *q, dw4_fb *fb, int idx, int nthreads)
{
    if (!q || q->n <= 0)
        return -1;
    idx %= q->n;
    if (idx < 0)
        idx += q->n;
    return dw4_ui_draw_file(fb, q->paths[idx], q->texdir, nthreads, q->hide, q->sx, q->sy);
}

int dw4_uiseq_draw_at(dw4_uiseq *q, dw4_fb *fb, double secs, double fps, int nthreads)
{
    return dw4_uiseq_draw(q, fb, (int)(secs * (fps > 0.0 ? fps : 1.0)), nthreads);
}

void dw4_uiseq_close(dw4_uiseq *q)
{
    if (!q)
        return;
    free(q->paths);
    free(q->texdir);
    free(q->hide);
    free(q);
}
