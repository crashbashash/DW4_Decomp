#include "dw4/stagesound.h"
#include "dw4/igb.h"
#include "dw4/igfile.h"
#include "dw4/sfp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define PACKS 8
#define BANKS 32

struct pack {
    const uint8_t *data;
    uint32_t size;
    dw4_igb g;
    int open;
    uint32_t list;                 /* beSoundInfo._fnameList */
    dw4_sfp_bank banks[BANKS];     /* the resident banks embedded in this pack, named by their beCriSfpData records */
    unsigned nbanks;
};
struct dw4_stagesound {
    struct pack pack[PACKS];
    unsigned npack;
    dw4_stagesound_entry *entry;
    unsigned count, cap;
    const uint8_t *global;         /* sbiallse.igb, the shared allse.sfp bank */
    uint32_t global_size;
    dw4_sfp_bank global_bank;
    int has_global;
};

static uint32_t value(const dw4_igb_record *r, unsigned slot)
{
    for (unsigned i = 0; i < r->nvalues; i++)
        if (r->values[i].ordinal == slot) return r->values[i].raw;
    return 0;
}
static uint32_t le32(const uint8_t *p)
{ return p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24; }
static uint32_t be32(const uint8_t *p)
{ return (uint32_t)p[0] << 24 | (uint32_t)p[1] << 16 | (uint32_t)p[2] << 8 | p[3]; }

/* beSoundInfo._fnameList -> igNamedObjectList._data -> named object IDs. */
static int filename(dw4_igb *g, uint32_t list, unsigned index, char *out, size_t cap)
{
    dw4_igb_record r;
    uint32_t off, len, block;
    const uint8_t *p;
    if (dw4_igb_ref(g, list, &off, NULL) != 2 || !dw4_igb_decode(g, off, &r)) return -1;
    block = value(&r, 4);
    dw4_igb_record_free(&r);
    p = dw4_igb_block(g, block, &len);
    if (!p || index >= len / 4 || dw4_igb_ref(g, le32(p + index * 4), &off, NULL) != 2 ||
        !dw4_igb_decode(g, off, &r)) return -1;
    if (!r.name) { dw4_igb_record_free(&r); return -1; }
    snprintf(out, cap, "%s", r.name);
    dw4_igb_record_free(&r);
    return 0;
}

static int add(dw4_stagesound *s, const dw4_stagesound_entry *e)
{
    if (s->count == s->cap) {
        unsigned cap = s->cap ? s->cap * 2 : 64;
        dw4_stagesound_entry *n = realloc(s->entry, cap * sizeof *n);
        if (!n) return -1;
        s->entry = n; s->cap = cap;
    }
    s->entry[s->count++] = *e;
    return 0;
}

dw4_stagesound *dw4_stagesound_open(dw4_mount *mnt, const char *stage)
{
    dw4_stagesound *s = calloc(1, sizeof *s);
    dw4_ref refs[PACKS];
    uint32_t nr;
    if (!s) return NULL;
    nr = dw4_igfile_stage_refs(mnt, stage, refs, PACKS);
    for (uint32_t i = 0; i < nr && i < PACKS; i++) {
        struct pack *pk = &s->pack[s->npack];
        int base_volume = 0;
        pk->data = dw4_mount_entry(mnt, refs[i].pt, refs[i].entry, &pk->size, NULL);
        if (!pk->data || dw4_igb_open(&pk->g, pk->data, pk->size, 0)) continue;
        if (dw4_igb_refs_open(&pk->g)) { dw4_igb_close(&pk->g); continue; }
        pk->open = 1;
        for (uint32_t off = pk->g.chain2_off, n = 0; n < pk->g.chain2_n; n++) {
            dw4_igb_record r;
            if (!dw4_igb_decode(&pk->g, off, &r)) break;
            if (!strcmp(r.class_name, "beSoundInfo")) {
                pk->list = value(&r, 7);
                base_volume = (int16_t)value(&r, 9);
            }
            off = r.end; dw4_igb_record_free(&r);
        }
        if (!pk->list) { dw4_igb_close(&pk->g); pk->open = 0; continue; }
        for (uint32_t off = pk->g.chain2_off, n = 0; n < pk->g.chain2_n; n++) {
            dw4_igb_record r;
            dw4_stagesound_entry e;
            if (!dw4_igb_decode(&pk->g, off, &r)) break;
            if (!strcmp(r.class_name, "beSoundData") && r.name) {
                memset(&e, 0, sizeof e);
                snprintf(e.name, sizeof e.name, "%s", r.name);
                e.type = (int16_t)value(&r, 4);
                e.fname_idx = (int16_t)value(&r, 5);
                e.memory_idx = value(&r, 6);
                e.channel = (int16_t)value(&r, 7);
                e.volume = (int16_t)value(&r, 8);
                e.priority = (int16_t)value(&r, 9);
                e.base_volume = base_volume;
                e.pack = (int)s->npack;
                if (filename(&pk->g, pk->list, (unsigned)e.fname_idx, e.file, sizeof e.file)) e.file[0] = 0;
                if (add(s, &e)) { dw4_igb_record_free(&r); dw4_stagesound_close(s); return NULL; }
            }
            off = r.end; dw4_igb_record_free(&r);
        }
        pk->nbanks = dw4_sfp_scan(pk->data, pk->size, pk->banks, BANKS);
        if (pk->nbanks > BANKS) pk->nbanks = 0;
        else dw4_sfp_bank_names(&pk->g, pk->banks, pk->nbanks);
        s->npack++;
    }
    if (!s->npack) { dw4_stagesound_close(s); return NULL; }
    s->global = dw4_mount_data(mnt, "sbiallse.igb", &s->global_size);
    if (s->global) {
        dw4_sfp_bank b[2];
        if (dw4_sfp_scan(s->global, s->global_size, b, 2) == 1) { s->global_bank = b[0]; s->has_global = 1; }
    }
    return s;
}
void dw4_stagesound_close(dw4_stagesound *s)
{
    if (!s) return;
    for (unsigned i = 0; i < s->npack; i++) if (s->pack[i].open) dw4_igb_close(&s->pack[i].g);
    free(s->entry);
    free(s);
}
dw4_igb *dw4_stagesound_pack_igb(const dw4_stagesound *s, unsigned pack)
{ return s && pack < s->npack && s->pack[pack].open ? (dw4_igb *)&s->pack[pack].g : NULL; }
unsigned dw4_stagesound_count(const dw4_stagesound *s) { return s ? s->count : 0; }
const dw4_stagesound_entry *dw4_stagesound_at(const dw4_stagesound *s, unsigned index)
{ return s && index < s->count ? &s->entry[index] : NULL; }
const dw4_stagesound_entry *dw4_stagesound_find(const dw4_stagesound *s, const char *name)
{
    if (!s || !name) return NULL;
    for (unsigned i = 0; i < s->count; i++) if (!strcmp(s->entry[i].name, name)) return &s->entry[i];
    return NULL;
}

static int resident(const uint8_t *p, size_t n, const dw4_sfp_bank *bank, unsigned index, dw4_audio_clip *c)
{
    dw4_sfp_entry e[256];
    unsigned ne = dw4_sfp_entries(p, n, bank, e, 256);
    size_t count;
    int16_t *mono;
    int rc;
    if (ne > 256 || index >= ne) return -1;
    count = (size_t)(e[index].end - e[index].start) / 16 * 28;
    mono = malloc(count * sizeof(*mono));
    if (!mono) return -1;
    count = dw4_vag_decode(p + bank->vag_off + e[index].start, e[index].end - e[index].start, mono, count);
    rc = dw4_audio_from_mono(mono, count, e[index].rate ? (int)e[index].rate : (int)bank->rate, c);
    free(mono);
    return rc;
}

/* The resident bank a cue's file names: the shared allse bank, or one of the pack's own. A pack's banks are named by matching the
 * beCriSfpData size, which two banks of equal size can swap (the cannon banks of stag0204/0304/0401), so a named bank that does
 * not hold the cue's sequence group gives way to the pack bank whose directory does: a group tag is unique within a pack. */
static int bank_of(const dw4_stagesound *s, const dw4_stagesound_entry *r, const uint8_t **data, uint32_t *size, const dw4_sfp_bank **bank)
{
    const struct pack *pk = &s->pack[r->pack];
    const char *base = strrchr(r->file, '/');
    const uint8_t *ev;
    const dw4_sfp_bank *named = NULL;
    base = base ? base + 1 : r->file;
    if (!strcasecmp(base, "allse.sfp")) {
        if (!s->has_global) return -1;
        *data = s->global; *size = s->global_size; *bank = &s->global_bank;
        return 0;
    }
    for (unsigned i = 0; i < pk->nbanks; i++)
        if (!strcasecmp(base, pk->banks[i].name)) { named = &pk->banks[i]; break; }
    if (named && (r->memory_idx == 0xffffffffu || !dw4_sfp_sequence(pk->data, pk->size, named, r->memory_idx, &ev, NULL, NULL))) {
        *data = pk->data; *size = pk->size; *bank = named;
        return 0;
    }
    for (unsigned i = 0; i < pk->nbanks; i++)
        if (&pk->banks[i] != named && !dw4_sfp_sequence(pk->data, pk->size, &pk->banks[i], r->memory_idx, &ev, NULL, NULL)) {
            *data = pk->data; *size = pk->size; *bank = &pk->banks[i];
            return 0;
        }
    if (named) { *data = pk->data; *size = pk->size; *bank = named; return 0; }
    return -1;
}
int dw4_stagesound_events(const dw4_stagesound *s, const dw4_stagesound_entry *r, const uint8_t **events, size_t *available)
{
    const uint8_t *p;
    uint32_t size;
    const dw4_sfp_bank *bank;
    if (!s || !r || r->pack < 0 || (unsigned)r->pack >= s->npack || r->memory_idx == 0xffffffffu) return -1;
    if (bank_of(s, r, &p, &size, &bank)) return -1;
    return dw4_sfp_sequence(p, size, bank, r->memory_idx, events, available, NULL);
}

int dw4_stagesound_decode(const dw4_stagesound *s, const dw4_mount *mnt, const dw4_stagesound_entry *r, dw4_audio_clip *c, const char *label)
{
    const char *file, *base;
    int pt, entry;
    uint32_t size = 0, wave;
    const uint8_t *p;
    const dw4_sfp_bank *bank = NULL;
    if (!s || !mnt || !r || !c || r->pack < 0 || (unsigned)r->pack >= s->npack || !r->file[0]) return DW4_STAGESOUND_NOFILE;
    file = r->file;
    if (sscanf(file, "[%d.%d]", &pt, &entry) == 2) {
        p = dw4_mount_entry(mnt, pt, entry, &size, NULL);
        if (!p || size < 0x38 || p[0] != 0x80 || p[1] != 0 || dw4_audio_decode_blob(p, size, c)) return DW4_STAGESOUND_NOSTREAM;
        /* The shipped streamed tracks are ADX v4. Loop fields follow the channel histories; retain the intro
         * and repeat only the authored loop. */
        if (p[18] == 4 && p[19] == 0 && p[7] <= 2 &&
            ((unsigned)p[2] * 256 + p[3] + 4) >= 0x38 + 6 && be32(p + 0x24)) {
            unsigned rate = be32(p + 8);
            if (rate) {
                size_t start = (uint64_t)be32(p + 0x28) * 48000 / rate;
                size_t end = (uint64_t)be32(p + 0x30) * 48000 / rate;
                if (start < end && end <= c->frames) { c->loop_start = start; c->loop_end = end; }
            }
        }
        if (label) printf("  %s audio: %s -> %s, %zu frames, loop %zu..%zu\n", label, r->name, file, c->frames, c->loop_start, c->loop_end);
        return 0;
    }
    if (bank_of(s, r, &p, &size, &bank)) return DW4_STAGESOUND_NOBANK;
    base = strrchr(file, '/');
    base = base ? base + 1 : file;
    if (dw4_sfp_resolve(p, size, bank, r->memory_idx, &wave)) return DW4_STAGESOUND_NOSEQ;
    if (resident(p, size, bank, wave, c)) return DW4_STAGESOUND_NOWAVE;
    if (label) printf("  %s audio: %s -> %s sequence %u, waveform %u, %zu frames\n", label, r->name, base, r->memory_idx >> 16, wave, c->frames);
    return 0;
}
