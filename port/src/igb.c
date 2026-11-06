/* igb.c — igBinary container reader.  See dw4/igb.h.
 *
 * The walk and the record decode mirror DW4_Decomp/scripts/igb_dir.py and
 * igb_inst.py, including the two properties that make them self-checking:
 * the directory walk validates every triple, and a record decode must land exactly
 * on its own `recordSize`.
 */
#include "dw4/igb.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IGB_MAXTRIPLES 600u

static uint16_t rd16(const uint8_t *p) { return (uint16_t)(p[0] | (p[1] << 8)); }
static uint32_t rd32(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}
static uint64_t rd64(const uint8_t *p)
{
    return (uint64_t)rd32(p) | ((uint64_t)rd32(p + 4) << 32);
}
static uint32_t align2(uint32_t x) { return (x + 1u) & ~1u; }
static uint32_t align4(uint32_t x) { return (x + 3u) & ~3u; }

/* ---- identifiers ---------------------------------------------------------- */

typedef struct {
    uint32_t off;
    uint32_t len;              /* excluding the NUL */
    const char *p;
} igb_ident;

typedef struct {
    igb_ident *v;
    uint32_t n;
} igb_idents;

static int ident_at(const uint8_t *b, size_t size, uint32_t off,
                    uint32_t *len_out, const char **p_out)
{
    uint32_t i = off, n = 0;

    if (off >= size)
        return 0;
    if (!((b[off] >= 'A' && b[off] <= 'Z') || (b[off] >= 'a' && b[off] <= 'z') ||
          b[off] == '_'))
        return 0;
    i = off;
    while (i < size) {
        uint8_t c = b[i];
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9') || c == '_' || c == ':') {
            n++;
            i++;
            continue;
        }
        break;
    }
    if (i >= size || b[i] != 0 || n < 3 || n > 61)
        return 0;
    *len_out = n;
    *p_out = (const char *)(b + off);
    return 1;
}

static int ident_cmp(const void *a, const void *b)
{
    uint32_t x = ((const igb_ident *)a)->off, y = ((const igb_ident *)b)->off;
    return x < y ? -1 : (x > y ? 1 : 0);
}

static const igb_ident *idents_find(const igb_idents *ids, uint32_t off)
{
    uint32_t lo = 0, hi = ids->n;

    while (lo < hi) {
        uint32_t mid = lo + (hi - lo) / 2;
        if (ids->v[mid].off == off)
            return &ids->v[mid];
        if (ids->v[mid].off < off)
            lo = mid + 1;
        else
            hi = mid;
    }
    return NULL;
}

static void scan_idents(const uint8_t *b, size_t size, uint32_t start, uint32_t limit,
                        igb_idents *out)
{
    uint32_t i = start;

    out->v = NULL;
    out->n = 0;
    if (limit > size)
        limit = (uint32_t)size;
    while (i < limit) {
        uint32_t len;
        const char *p;
        if (ident_at(b, size, i, &len, &p)) {
            igb_ident *nv = (igb_ident *)realloc(out->v, (out->n + 1) * sizeof(*nv));
            if (!nv)
                return;
            out->v = nv;
            out->v[out->n].off = i;
            out->v[out->n].len = len;
            out->v[out->n].p = p;
            out->n++;
            i += len + 1;
        } else {
            i++;
        }
    }
    qsort(out->v, out->n, sizeof(*out->v), ident_cmp);
}

static int triples_ok(const uint8_t *b, size_t size, uint32_t pad, uint32_t n)
{
    uint32_t k;

    for (k = 0; k < n; k++) {
        uint32_t p = pad + 6 * k;
        if (p + 6 > size)
            return 0;
        if (rd16(b + p) >= DW4_IGB_MAXSFX || rd16(b + p + 2) < 1 || rd16(b + p + 2) >= 4096)
            return 0;
    }
    return 1;
}

/* ---- directory walk ------------------------------------------------------- */

static void push_class(dw4_igb *g, const igb_ident *id, const uint8_t *b,
                       uint32_t pad, uint32_t n)
{
    dw4_igb_class *c = (dw4_igb_class *)realloc(g->classes,
                                                (g->nclasses + 1) * sizeof(*c));
    uint32_t k;
    char *nm;

    if (!c)
        return;
    g->classes = c;
    c = &g->classes[g->nclasses];
    nm = (char *)malloc(id->len + 1);
    if (!nm)
        return;
    memcpy(nm, id->p, id->len);
    nm[id->len] = 0;
    c->name = nm;
    c->off = id->off;
    c->ntriples = n;
    c->triples = n ? (dw4_igb_triple *)calloc(n, sizeof(*c->triples)) : NULL;
    for (k = 0; k < n; k++) {
        c->triples[k].type = rd16(b + pad + 6 * k);
        c->triples[k].ordinal = rd16(b + pad + 6 * k + 2);
        c->triples[k].size = rd16(b + pad + 6 * k + 4);
    }
    g->nclasses++;
}

static void walk_directory(dw4_igb *g, uint32_t start, uint32_t limit)
{
    igb_idents ids;
    const igb_ident *cur;

    scan_idents(g->data, g->size, start, limit, &ids);
    if (!ids.n) {
        free(ids.v);
        return;
    }
    cur = &ids.v[0];
    while (cur) {
        uint32_t pad = align2(cur->off + cur->len + 1);
        uint32_t n, best = 0;
        int found = 0;

        for (n = 0; n < IGB_MAXTRIPLES; n++) {
            uint32_t cand = pad + 6 * n;
            if (cand > limit)
                break;
            if (cand > cur->off && idents_find(&ids, cand) && triples_ok(g->data, g->size, pad, n)) {
                best = n;
                found = 1;
                break;
            }
        }
        if (found) {
            push_class(g, cur, g->data, pad, best);
            g->dir_end = pad + 6 * best;
            cur = idents_find(&ids, g->dir_end);
            continue;
        }
        /* the final class has no next name to sit at a 6-aligned offset: emit the
         * longest valid prefix and stop */
        n = 0;
        while (triples_ok(g->data, g->size, pad, n + 1))
            n++;
        if (n) {
            push_class(g, cur, g->data, pad, n);
            g->dir_end = pad + 6 * n;
        }
        break;
    }
    free(ids.v);
}

static uint32_t find_directory_start(const dw4_igb *g)
{
    static const char anchor[] = "\0igObject\0";
    uint32_t best = 0, bestn = 0, i;
    size_t lim = g->size < 0x8000 ? g->size : 0x8000;

    for (i = 0; i + sizeof(anchor) <= lim; i++) {
        uint32_t cand, n;
        dw4_igb probe;

        if (memcmp(g->data + i, anchor, sizeof(anchor) - 1) != 0)
            continue;
        cand = i + 1;
        memset(&probe, 0, sizeof(probe));
        probe.data = g->data;
        probe.size = g->size;
        walk_directory(&probe, cand, (uint32_t)(g->size < cand + 0x8000 ? g->size : cand + 0x8000));
        n = probe.nclasses;
        dw4_igb_close(&probe);
        if (n > bestn) {
            bestn = n;
            best = cand;
        }
    }
    return best;
}

/* ---- string table --------------------------------------------------------- */

static void parse_strings(dw4_igb *g)
{
    uint32_t i, pos;

    g->nstrings = g->header[9];
    if (!g->nstrings)
        return;
    if (0x30 + (size_t)g->nstrings * 12 > g->size)
        return;
    pos = 0x30 + g->nstrings * 12;
    g->strings = (const char **)calloc(g->nstrings, sizeof(*g->strings));
    if (!g->strings)
        return;
    for (i = 0; i < g->nstrings; i++) {
        uint32_t len = rd32(g->data + 0x30 + 12 * i);
        if (!len || pos + len > g->size) {
            g->strings[i] = "";
            continue;
        }
        g->strings[i] = (const char *)(g->data + pos);
        pos += len;
    }
}

/* ---- records -------------------------------------------------------------- */

void dw4_igb_close(dw4_igb *g)
{
    uint32_t i;

    for (i = 0; i < g->nclasses; i++) {
        if (g->classes[i].name)
            free(g->classes[i].name);
        free(g->classes[i].triples);
    }
    free(g->classes);
    free((void *)g->strings);
    free(g->id_off);
    free(g->id_len);
    free(g->id_kind);
    memset(g, 0, sizeof(*g));
}

int dw4_igb_open(dw4_igb *g, const uint8_t *blob, size_t size, uint32_t start)
{
    int i;

    memset(g, 0, sizeof(*g));
    g->data = blob;
    g->size = size;
    if (size < 0x30)
        return -1;
    for (i = 0; i < 12; i++)
        g->header[i] = rd32(blob + 4 * i);
    /* hdr[0] is 0x00000100 in the manifest NDMW.IGB but the meaning of the header
     * words is file-specific (a stage/model pack uses [4]/[5] for its content sizes),
     * so it is reported, not required.  The directory walk is the real validation. */
    parse_strings(g);
    if (!start)
        start = find_directory_start(g);
    if (!start)
        return -1;
    g->dir_off = start;
    walk_directory(g, start, (uint32_t)size);
    return g->nclasses ? 0 : -1;
}

const dw4_igb_class *dw4_igb_find_class(const dw4_igb *g, const char *name)
{
    uint32_t i;

    for (i = 0; i < g->nclasses; i++)
        if (strcmp(g->classes[i].name, name) == 0)
            return &g->classes[i];
    return NULL;
}

/* Validate the record at `off` and return its end offset, without building values.
 * This is the hot path: a chain scan visits every record, and allocating a value
 * array per record made the 5 MB model pack take 30 seconds. */
static int record_extent(const dw4_igb *g, uint32_t off, uint32_t *end_out)
{
    uint32_t cl, recsize, q, k;
    const dw4_igb_class *c;

    if ((size_t)off + 8 > g->size)
        return 0;
    cl = rd32(g->data + off);
    recsize = rd32(g->data + off + 4);
    if (cl >= g->nclasses || recsize < 8 || (size_t)off + recsize > g->size)
        return 0;
    c = &g->classes[cl];
    q = off + 8;
    for (k = 0; k < c->ntriples; k++) {
        const dw4_igb_triple *t = &c->triples[k];
        if (t->type == 4) {
            uint32_t n;
            if ((size_t)q + 4 > g->size)
                return 0;
            n = rd32(g->data + q);
            if ((n & 3u) || n > 8192 || (size_t)q + 4 + n > g->size)
                return 0;
            if (n && g->data[q + 4 + n - 1] != 0)
                return 0;
            q += 4 + n;
        } else {
            uint32_t w = align4(t->size);
            if ((size_t)q + w > g->size)
                return 0;
            q += w;
        }
    }
    if (q - off != recsize)
        return 0;
    *end_out = q;
    return 1;
}

int dw4_igb_record_end(const dw4_igb *g, uint32_t off, uint32_t *end_out)
{
    return record_extent(g, off, end_out);
}

int dw4_igb_decode(const dw4_igb *g, uint32_t off, dw4_igb_record *out)
{
    uint32_t cl, recsize, q, k;
    const dw4_igb_class *c;

    if ((size_t)off + 8 > g->size)
        return 0;
    cl = rd32(g->data + off);
    recsize = rd32(g->data + off + 4);
    if (cl >= g->nclasses || recsize < 8 || (size_t)off + recsize > g->size)
        return 0;
    c = &g->classes[cl];
    memset(out, 0, sizeof(*out));
    q = off + 8;
    out->values = c->ntriples ? (dw4_igb_value *)calloc(c->ntriples, sizeof(*out->values))
                              : NULL;
    if (c->ntriples && !out->values)
        return 0;
    for (k = 0; k < c->ntriples; k++) {
        dw4_igb_value *v = &out->values[k];
        const dw4_igb_triple *t = &c->triples[k];

        v->type = t->type;
        v->ordinal = t->ordinal;
        if (t->type == 4) {
            uint32_t n;
            if ((size_t)q + 4 > g->size)
                goto fail;
            n = rd32(g->data + q);
            if ((n & 3u) || n > 8192 || (size_t)q + 4 + n > g->size)
                goto fail;
            if (n && g->data[q + 4 + n - 1] != 0)
                goto fail;
            v->str = n ? (const char *)(g->data + q + 4) : "";
            v->voff = q + 4;
            v->vsize = n;
            if (!out->name)
                out->name = v->str;
            q += 4 + n;
            continue;
        }
        {
            uint32_t w = align4(t->size);
            if ((size_t)q + w > g->size)
                goto fail;
            v->raw = rd32(g->data + q);
            if (w >= 8)
                v->raw64 = rd64(g->data + q);
            v->voff = q;
            v->vsize = w;
            q += w;
        }
    }
    if (q - off != recsize)
        goto fail;
    out->off = off;
    out->class_index = cl;
    out->size = recsize;
    out->class_name = c->name;
    out->nvalues = c->ntriples;
    out->end = q;
    return 1;
fail:
    free(out->values);
    memset(out, 0, sizeof(*out));
    return 0;
}

void dw4_igb_record_free(dw4_igb_record *r)
{
    free(r->values);
    memset(r, 0, sizeof(*r));
}

uint32_t dw4_igb_chain(const dw4_igb *g, uint32_t off, dw4_igb_record *out, uint32_t cap)
{
    uint32_t n = 0, p = off, end;

    if (!out) {
        while (record_extent(g, p, &end)) {
            n++;
            p = end;
        }
        return n;
    }
    for (;;) {
        dw4_igb_record r;
        if (!dw4_igb_decode(g, p, &r))
            return n;
        end = r.end;
        if (n < cap)
            out[n] = r;
        else
            dw4_igb_record_free(&r);
        n++;
        p = end;
    }
}

uint32_t dw4_igb_find_chain(const dw4_igb *g, uint32_t lo)
{
    uint32_t p, best = 0, bestn = 0, end;
    uint8_t *covered;

    /* Records tile without gaps, so a chain is maximal -- but a pack's records can begin
     * on either parity (the stage packs at 2-mod-4, the character model packs `p_*.igb`
     * at the other), so every offset is tried rather than stepping by two.  A record
     * start is a *chain* start only when no other record ends on it, so the walk skips
     * whole chains without the old `p = q` jump that could leap over a start. */
    covered = (uint8_t *)calloc((size_t)g->size + 1, 1);
    if (!covered)
        return 0;
    for (p = lo; (size_t)p + 8 < g->size; p++)
        if (record_extent(g, p, &end))
            covered[end] = 1;
    for (p = lo; (size_t)p + 8 < g->size; p++) {
        uint32_t n, q;

        if (covered[p] || !record_extent(g, p, &end))
            continue;
        n = 1;
        q = end;
        while (record_extent(g, q, &end)) {
            n++;
            q = end;
        }
        if (n > bestn) {
            bestn = n;
            best = p;
        }
    }
    free(covered);
    return best;
}

/* ---- references: the id remap table and the content pool ------- */

typedef struct {
    uint32_t off, n, end;
} igb_chain;

/* Every maximal chain of more than one record, in file order.  Records tile without
 * gaps, so a decode failure ends a chain and the next one starts later.  As in
 * `dw4_igb_find_chain`, every offset is tried (the character model packs start on the
 * odd parity) and a start inside a chain already taken is dropped. */
static uint32_t chains_enumerate(const dw4_igb *g, uint32_t lo, igb_chain **out)
{
    igb_chain *v = NULL;
    uint32_t n = 0, p, end, far = 0;
    uint8_t *covered;

    *out = NULL;
    covered = (uint8_t *)calloc((size_t)g->size + 1, 1);
    if (!covered)
        return 0;
    for (p = lo; (size_t)p + 8 < g->size; p++)
        if (record_extent(g, p, &end))
            covered[end] = 1;
    for (p = lo; (size_t)p + 8 < g->size; p++) {
        uint32_t q, cnt;

        if (covered[p] || !record_extent(g, p, &end))
            continue;
        cnt = 1;
        q = end;
        while (record_extent(g, q, &end)) {
            cnt++;
            q = end;
        }
        if (p < far)                 /* a false start inside a chain already taken */
            continue;
        if (q > far)
            far = q;
        if (cnt > 1) {
            igb_chain *nv = (igb_chain *)realloc(v, (n + 1) * sizeof(*nv));
            if (!nv)
                break;
            v = nv;
            v[n].off = p;
            v[n].n = cnt;
            v[n].end = q;
            n++;
        }
    }
    free(covered);
    *out = v;
    return n;
}

static void refs_clear(dw4_igb *g)
{
    free(g->id_off);
    free(g->id_len);
    free(g->id_kind);
    g->id_off = NULL;
    g->id_len = NULL;
    g->id_kind = NULL;
    g->chain1_off = g->chain1_n = g->chain2_off = g->chain2_n = 0;
    g->table_off = g->table_n = g->pool_off = g->pool_sum = 0;
}

/* One value of a section-1 record by its slot ordinal (the triples carry the
 * ordinal, so this needs no reflection table). */
static uint32_t rec_value(const dw4_igb_record *r, uint32_t ordinal)
{
    uint32_t k;

    for (k = 0; k < r->nvalues; k++)
        if (r->values[k].ordinal == ordinal)
            return r->values[k].raw;
    return 0;
}

int dw4_igb_refs_open(dw4_igb *g)
{
    igb_chain *ch = NULL;
    uint32_t nch, i, p, end, tcnt = 0, table = 0, run, objk;
    uint32_t s1n, s2n;
    uint32_t *s1_obj = NULL, *s1_meta = NULL, *s1_size = NULL;
    uint32_t *s2_cls = NULL, *s2_off = NULL, *s2_len = NULL;
    int ok = 0;

    if (g->id_kind)
        return 0;                       /* already built */
    nch = chains_enumerate(g, g->dir_end ? g->dir_end : 0x800, &ch);
    if (nch < 2)
        goto done;
    s1n = ch[0].n;                      /* section 1: the memory/object directory */
    s2n = ch[1].n;                      /* section 2: the objects */
    s1_obj = (uint32_t *)calloc(s1n, sizeof(*s1_obj));
    s1_meta = (uint32_t *)calloc(s1n, sizeof(*s1_meta));
    s1_size = (uint32_t *)calloc(s1n, sizeof(*s1_size));
    s2_cls = (uint32_t *)calloc(s2n, sizeof(*s2_cls));
    s2_off = (uint32_t *)calloc(s2n, sizeof(*s2_off));
    s2_len = (uint32_t *)calloc(s2n, sizeof(*s2_len));
    if (!s1_obj || !s1_meta || !s1_size || !s2_cls || !s2_off || !s2_len)
        goto done;

    for (i = 0, p = ch[0].off; i < s1n; i++) {
        dw4_igb_record r;

        if (!dw4_igb_decode(g, p, &r))
            goto done;
        s1_obj[i] = (strcmp(r.class_name, "igObjectDirEntry") == 0);
        s1_meta[i] = rec_value(&r, 11);     /* _typeMetaIndex */
        s1_size[i] = rec_value(&r, 7);      /* _memSize */
        p = r.end;
        dw4_igb_record_free(&r);
    }
    for (i = 0, p = ch[1].off; i < s2n; i++) {
        if (!record_extent(g, p, &end))
            goto done;
        s2_cls[i] = rd32(g->data + p);
        s2_off[i] = p;
        s2_len[i] = end - p;
        p = end;
    }

    /* The remap table sits between the two sections.  Validate a candidate by its
     * own header (tableBytes == 8 + 2*idCount), that every entry indexes section 1,
     * and -- the strong check -- that the object entries' classes are exactly section
     * 2's record classes in order. */
    for (p = ch[0].end; p + 8 <= ch[1].off; p += 2) {
        uint32_t tb = rd32(g->data + p), c = rd32(g->data + p + 4);
        uint32_t n = 0;

        if (!c || c > (1u << 20) || tb != 8 + 2 * c)
            continue;
        if ((size_t)p + 8 + 2 * (size_t)c > g->size)
            continue;
        for (i = 0; i < c; i++) {
            uint32_t e = rd16(g->data + p + 8 + 2 * i);
            if (e >= s1n)
                break;
            if (s1_obj[e]) {
                if (n >= s2n || s1_meta[e] != s2_cls[n])
                    break;
                n++;
            }
        }
        if (i == c && n == s2n) {
            table = p;
            tcnt = c;
            break;
        }
    }
    if (!table)
        goto done;

    g->id_off = (uint32_t *)malloc(tcnt * sizeof(*g->id_off));
    g->id_len = (uint32_t *)malloc(tcnt * sizeof(*g->id_len));
    g->id_kind = (uint8_t *)calloc(tcnt, 1);
    if (!g->id_off || !g->id_len || !g->id_kind)
        goto done;
    g->chain1_off = ch[0].off;
    g->chain1_n = s1n;
    g->chain2_off = ch[1].off;
    g->chain2_n = s2n;
    g->table_off = table;
    g->table_n = tcnt;
    g->pool_off = ch[1].end;

    run = 0;
    objk = 0;
    for (i = 0; i < tcnt; i++) {
        uint32_t e = rd16(g->data + table + 8 + 2 * i);

        if (s1_obj[e]) {
            g->id_kind[i] = 2;
            g->id_off[i] = s2_off[objk];
            g->id_len[i] = s2_len[objk];
            objk++;
        } else {
            g->id_kind[i] = 1;
            g->id_off[i] = g->pool_off + run;
            g->id_len[i] = s1_size[e];
            /* A block is placed at a 4-byte boundary, so a `_memSize` that is not a
             * multiple of 4 is followed by 1-3 padding bytes.  Without
             * this the offsets drift, which is what the old ~141-byte "residual" on the
             * model packs was: sum(align4(_memSize)) is the pool size exactly. */
            run += (s1_size[e] + 3u) & ~3u;
        }
    }
    g->pool_sum = run;
    ok = 1;

done:
    if (!ok && g->id_kind)
        refs_clear(g);                  /* partially built: leave nothing behind */
    free(s1_obj);
    free(s1_meta);
    free(s1_size);
    free(s2_cls);
    free(s2_off);
    free(s2_len);
    free(ch);
    return ok ? 0 : -1;
}

int dw4_igb_ref(const dw4_igb *g, uint32_t id, uint32_t *off, uint32_t *len)
{
    if (!g->id_kind || id >= g->table_n)
        return 0;
    if (off)
        *off = g->id_off[id];
    if (len)
        *len = g->id_len[id];
    return g->id_kind[id];
}

const uint8_t *dw4_igb_block(const dw4_igb *g, uint32_t id, uint32_t *len_out)
{
    if (!g->id_kind || id >= g->table_n || g->id_kind[id] != 1)
        return NULL;
    if (len_out)
        *len_out = g->id_len[id];
    return g->data + g->id_off[id];
}
