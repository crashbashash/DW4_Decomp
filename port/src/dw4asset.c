#define _POSIX_C_SOURCE 200809L   /* mkstemp */
/* dw4asset.c — the port's asset CLI.
 *
 *   dw4asset afs <archive>                       entry table summary
 *   dw4asset cat <archive> <index> <out>         extract one entry
 *   dw4asset igb <file> [--at OFF]               igBinary header + class directory
 *   dw4asset igb --afs A --entry N [--at OFF]    the same, for an AFS entry
 *   dw4asset records <file> [--at OFF] [--class NAME]
 *   dw4asset reflect <file>|--afs A --entry N [--class NAME] [--limit N] [--json]
 *                       construct each record as a reflection-typed igObject (P2.6)
 *
 * It is deliberately a thin shell over libdw4asset: the point of the port's asset
 * layer is the library, and the CLI is how it is checked against the repository's
 * Python decoders (see tools/crosscheck.sh).
 */
#include "dw4/afs.h"
#include "dw4/platform.h"
#include "dw4/igb.h"
#include "dw4/manifest.h"
#include "dw4/mount.h"
#include "dw4/frontchr.h"
#include "dw4/png.h"
#include <time.h>
#include <math.h>
#include "dw4/render.h"
#include "dw4/sfp.h"
#include "dw4/texture.h"
#include "dw4/igfile.h"
#include "dw4/mesh.h"
#include "dw4/render.h"
#include "dw4/models.h"
#include "dw4/object.h"
#include "dw4/scene.h"
#include "dw4/texpack.h"
#include "dw4/livetex.h"
#include "dw4/skin.h"
#include "dw4/pose.h"
#include "dw4/gl_render.h"
#include "dw4/uireplay.h"
#include "dw4/window.h"
#include "dw4/vk_present.h"
#include "dw4/wav.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <unistd.h>

static const char *g_class_filter;
static uint32_t g_shown;
static int g_hist_all;
static uint32_t g_at;     /* explicit chain start (0 = find the longest) */
static long g_ref_id = -1;  /* `refs --id K` */
static int g_ref_list;      /* `refs --list [N]` */
static int g_ref_check;     /* `refs --check` */
static const char *g_ref_dump;  /* `refs --id K --dump FILE` */
static int g_json;          /* `reflect --json` */
static uint32_t g_limit;    /* `reflect --limit N` (0 = all) */

static int read_file(const char *path, uint8_t **out, size_t *out_len)
{
    FILE *f = fopen(path, "rb");
    long n;

    if (!f)
        return -1;
    if (fseek(f, 0, SEEK_END) != 0 || (n = ftell(f)) < 0 || fseek(f, 0, SEEK_SET) != 0) {
        fclose(f);
        return -1;
    }
    *out = (uint8_t *)malloc((size_t)n ? (size_t)n : 1);
    if (!*out) {
        fclose(f);
        return -1;
    }
    if (n && fread(*out, 1, (size_t)n, f) != (size_t)n) {
        free(*out);
        fclose(f);
        return -1;
    }
    fclose(f);
    *out_len = (size_t)n;
    return 0;
}

static int cmd_afs(const char *path)
{
    dw4_afs a;
    uint32_t i;

    if (dw4_afs_open(&a, path) != 0) {
        fprintf(stderr, "afs: cannot read %s\n", path);
        return 1;
    }
    printf("archive %s\n  entries %u  size %zu bytes\n", path, a.count, a.size);
    for (i = 0; i < a.count && i < 8; i++)
        printf("  [%4u] off=0x%08x size=%-10u\n", i, a.entries[i].offset, a.entries[i].size);
    if (a.count > 8)
        printf("  ...\n  [%4u] off=0x%08x size=%-10u\n", a.count - 1,
               a.entries[a.count - 1].offset, a.entries[a.count - 1].size);
    dw4_afs_close(&a);
    return 0;
}

static int cmd_cat(const char *path, const char *idx, const char *out)
{
    dw4_afs a;
    long n;

    if (dw4_afs_open(&a, path) != 0) {
        fprintf(stderr, "cat: cannot read %s\n", path);
        return 1;
    }
    n = dw4_afs_extract(&a, (uint32_t)strtoul(idx, NULL, 0), out);
    if (n < 0) {
        fprintf(stderr, "cat: entry %s out of range or unwritable %s\n", idx, out);
        dw4_afs_close(&a);
        return 1;
    }
    printf("wrote %ld bytes to %s\n", n, out);
    dw4_afs_close(&a);
    return 0;
}

static int cmd_igb(const uint8_t *blob, size_t len, const char *label)
{
    dw4_igb g;
    uint32_t i, chain_off, chain_n = 0, bytes = 0, first = 0, last = 0, p;
    uint32_t *hist;

    if (dw4_igb_open(&g, blob, len, 0) != 0) {
        fprintf(stderr, "igb: %s is not an igBinary container\n", label);
        return 1;
    }
    printf("%s\n  magic 0x%08x version %u\n", label, g.header[0], g.header[1]);
    printf("  header[3] classes %u   walked %u   strings %u\n",
           g.header[3], g.nclasses, g.nstrings);
    printf("  directory +0x%x, last class at +0x%x\n", g.dir_off,
           g.nclasses ? g.classes[g.nclasses - 1].off : g.dir_off);
    for (i = 0; i < g.nclasses && i < 12; i++) {
        printf("    [%3u] %-34s %u descriptor(s)  @0x%x\n", i, g.classes[i].name,
               g.classes[i].ntriples, g.classes[i].off);
    }
    if (g.nclasses > 12)
        printf("    ... %u more\n", g.nclasses - 12);

    chain_off = g_at ? g_at : dw4_igb_find_chain(&g, 0x800);
    if (g_hist_all) {
        /* every maximal chain, not just the longest: a pack often holds several (object
         * data, the in-memory directory, the content pool's lists) */
        uint32_t p2;
        printf("  chains:");
        for (p2 = 0x800; (size_t)p2 + 8 < g.size;) {
            uint32_t end, n2 = 1, q;
            if (!dw4_igb_record_end(&g, p2, &end)) {
                p2 += 2;
                continue;
            }
            q = end;
            while (dw4_igb_record_end(&g, q, &end)) {
                n2++;
                q = end;
            }
            if (n2 > 1)
                printf(" +0x%x(%u)", p2, n2);
            p2 = q;
        }
        printf("\n");
    }
    hist = (uint32_t *)calloc(g.nclasses ? g.nclasses : 1, sizeof(uint32_t));
    for (p = chain_off; chain_off;) {
        dw4_igb_record r;
        if (!dw4_igb_decode(&g, p, &r))
            break;
        if (!chain_n)
            first = r.off;
        if (hist)
            hist[r.class_index]++;
        bytes += r.size;
        last = r.end;
        chain_n++;
        p = r.end;
        dw4_igb_record_free(&r);
    }
    printf("  records: chain +0x%x, %u record(s), %u bytes, +0x%x .. +0x%x\n",
           chain_off, chain_n, bytes, first, last);
    if (hist && chain_n) {
        int shown = 0;
        while (shown < (g_hist_all ? 4096 : 8)) {
            uint32_t best = 0, bi = 0;
            for (i = 0; i < g.nclasses; i++)
                if (hist[i] > best) {
                    best = hist[i];
                    bi = i;
                }
            if (!best)
                break;
            printf("    %-34s %u\n", g.classes[bi].name, best);
            hist[bi] = 0;
            shown++;
        }
    }
    free(hist);
    dw4_igb_close(&g);
    return 0;
}

static int cmd_records(const uint8_t *blob, size_t len, const char *label)
{
    dw4_igb g;
    uint32_t chain_off, chain_n, k;

    if (dw4_igb_open(&g, blob, len, 0) != 0) {
        fprintf(stderr, "records: %s is not an igBinary container\n", label);
        return 1;
    }
    chain_off = g_at ? g_at : dw4_igb_find_chain(&g, 0x800);
    chain_n = chain_off ? dw4_igb_chain(&g, chain_off, NULL, 0) : 0;
    printf("%s: chain 0x%x, %u record(s)\n", label, chain_off, chain_n);
    if (chain_n) {
        dw4_igb_record *recs = (dw4_igb_record *)calloc(chain_n, sizeof(*recs));
        if (recs && dw4_igb_chain(&g, chain_off, recs, chain_n) == chain_n) {
            for (k = 0; k < chain_n; k++) {
                uint32_t j;
                if (g_class_filter && strcmp(recs[k].class_name, g_class_filter) != 0)
                    continue;
                printf("0x%06x %-32s size=%-5u values=%u name=%s\n", recs[k].off,
                       recs[k].class_name, recs[k].size, recs[k].nvalues,
                       recs[k].name ? recs[k].name : "-");
                for (j = 0; j < recs[k].nvalues && j < 24; j++) {
                    const dw4_igb_value *v = &recs[k].values[j];
                    printf("      slot %-3u type %-3u ", v->ordinal, v->type);
                    if (v->type == 4)
                        printf("\"%s\"\n", v->str ? v->str : "");
                    else
                        printf("0x%08x (%u)\n", v->raw, v->raw);
                }
                g_shown++;
            }
            for (k = 0; k < chain_n; k++)
                dw4_igb_record_free(&recs[k]);
        }
        free(recs);
    }
    printf("shown %u record(s)\n", g_shown);
    dw4_igb_close(&g);
    return 0;
}

/* The runtime object model (P2.6): decode a pack's records and construct each as a `dw4_object`,
 * then read its fields back **by name** through the reflection schema.  This is the get/set path
 * a running engine needs; `tools/verify_object.py` diffs the output against the decompilation
 * repo's own decoder (`scripts/igb_inst.py`), field for field. */
static int cmd_reflect(const uint8_t *blob, size_t len, const char *label)
{
    dw4_igb g;
    uint32_t chain_off, chain_n, k, shown = 0;
    int first = 1;

    if (dw4_igb_open(&g, blob, len, 0) != 0) {
        fprintf(stderr, "reflect: %s is not an igBinary container\n", label);
        return 1;
    }
    chain_off = g_at ? g_at : dw4_igb_find_chain(&g, 0x800);
    chain_n = chain_off ? dw4_igb_chain(&g, chain_off, NULL, 0) : 0;
    if (g_json)
        printf("{\"pack\":\"%s\",\"chain\":%u,\"records\":[", label, chain_off);
    else
        printf("%s: chain 0x%x, %u record(s)\n", label, chain_off, chain_n);
    if (chain_n) {
        dw4_igb_record *recs = (dw4_igb_record *)calloc(chain_n, sizeof(*recs));
        if (recs && dw4_igb_chain(&g, chain_off, recs, chain_n) == chain_n) {
            for (k = 0; k < chain_n; k++) {
                dw4_object o;
                uint32_t j;
                if (g_class_filter && strcmp(recs[k].class_name, g_class_filter) != 0)
                    continue;
                if (g_limit && shown >= g_limit)
                    break;
                if (dw4_object_from_record(&o, &g, &recs[k]) != 0) {
                    dw4_igb_record_free(&recs[k]);
                    continue;
                }
                if (g_json) {
                    printf("%s{\"off\":%u,\"class\":\"%s\",\"K\":%d,\"fields\":{",
                           first ? "" : ",", recs[k].off, recs[k].class_name, o.K);
                    first = 0;
                } else {
                    printf("0x%06x %-30s size=%-5u K=%d name=%s\n", recs[k].off,
                           recs[k].class_name, recs[k].size, o.K,
                           recs[k].name ? recs[k].name : "-");
                }
                for (j = 0; o.mo && j < o.mo->nfields; j++) {
                    const dw4_metafield *f = &o.mo->fields[j];
                    if (g_json) {
                        printf("%s\"%s\":", j ? "," : "", f->name);
                    } else {
                        printf("    %-28s = ", f->name);
                    }
                    if (f->tid == 4) {
                        const char *s = dw4_object_get_str(&o, f->name);
                        if (g_json) printf("\"%s\"", s ? s : "");
                        else printf("\"%s\"\n", s ? s : "");
                    } else if (f->tid == 16) {
                        float v = dw4_object_get_f32(&o, f->name);
                        if (g_json) printf("%.6g", v);
                        else printf("%g\n", v);
                    } else if (f->tid == 36) {
                        float v[3];
                        dw4_object_get_vec3(&o, f->name, v);
                        if (g_json) printf("[%.6g,%.6g,%.6g]", v[0], v[1], v[2]);
                        else printf("(%g, %g, %g)\n", v[0], v[1], v[2]);
                    } else if (f->tid == 38) {
                        float v[4];
                        dw4_object_get_vec4(&o, f->name, v);
                        if (g_json) printf("[%.6g,%.6g,%.6g,%.6g]", v[0], v[1], v[2], v[3]);
                        else printf("(%g, %g, %g, %g)\n", v[0], v[1], v[2], v[3]);
                    } else {
                        int32_t v = dw4_object_get_int(&o, f->name);
                        if (g_json) printf("%d", v);
                        else printf("%d\n", v);
                    }
                }
                if (g_json) {
                    /* the field's descriptor type, so the checker can exclude a slot whose type
                     * does not match the record's (the ordinal map has known non-conformers) */
                    printf("},\"tid\":{");
                    for (j = 0; o.mo && j < o.mo->nfields; j++)
                        printf("%s\"%s\":%u", j ? "," : "", o.mo->fields[j].name,
                               (unsigned)o.mo->fields[j].tid);
                    printf("}}");
                }
                shown++;
                dw4_object_free(&o);
                dw4_igb_record_free(&recs[k]);
            }
            for (; k < chain_n; k++)
                dw4_igb_record_free(&recs[k]);
        }
        free(recs);
    }
    if (g_json)
        printf("]}\n");
    else
        printf("shown %u object(s)\n", shown);
    dw4_igb_close(&g);
    return 0;
}

/* The pack's reference tables: the id remap table between the two
 * object sections, and the content-pool block offsets (an igMemoryRef value is the id
 * of its block, so offset = pool_start + sum of _memSize of the block ids below it). */
static int cmd_refs(const uint8_t *blob, size_t len, const char *label)
{
    dw4_igb g;
    uint32_t i, j, nobj = 0, pool_bytes;

    if (dw4_igb_open(&g, blob, len, 0) != 0) {
        fprintf(stderr, "refs: %s is not an igBinary container\n", label);
        return 1;
    }
    if (dw4_igb_refs_open(&g) != 0) {
        printf("%s: no id remap table (not a two-section pack)\n", label);
        dw4_igb_close(&g);
        return 1;
    }
    for (i = 0; i < g.table_n; i++)
        if (g.id_kind[i] == 2)
            nobj++;
    pool_bytes = (uint32_t)(g.size - g.pool_off);
    printf("%s\n", label);
    printf("  section1 +0x%x (%u), section2 +0x%x (%u)\n",
           g.chain1_off, g.chain1_n, g.chain2_off, g.chain2_n);
    printf("  table +0x%x: %u id(s), %u object(s), %u block(s)\n",
           g.table_off, g.table_n, nobj, g.table_n - nobj);
    printf("  pool +0x%x: %u of %u bytes accounted\n", g.pool_off, g.pool_sum, pool_bytes);
    if (g_ref_check)
        printf("  check: %s %u\n", g.pool_sum == pool_bytes ? "exact" :
               (g.pool_sum > pool_bytes ? "over" : "short"),
               g.pool_sum > pool_bytes ? g.pool_sum - pool_bytes : pool_bytes - g.pool_sum);
    if (g_ref_id >= 0) {
        uint32_t off = 0, ln = 0;
        int kind = dw4_igb_ref(&g, (uint32_t)g_ref_id, &off, &ln);

        if (kind == 1) {
            printf("  id %ld -> block +0x%x len %u first ", g_ref_id, off, ln);
            for (i = 0; i < ln && i < 16; i++)
                printf("%02x", g.data[off + i]);
            printf("\n");
            if (g_ref_dump) {
                FILE *fp = fopen(g_ref_dump, "wb");
                if (!fp || fwrite(g.data + off, 1, ln, fp) != ln) {
                    fprintf(stderr, "refs: cannot write %s\n", g_ref_dump);
                    if (fp)
                        fclose(fp);
                    dw4_igb_close(&g);
                    return 1;
                }
                fclose(fp);
                printf("  wrote %u byte(s) to %s\n", ln, g_ref_dump);
            }
        } else if (kind == 2) {
            dw4_igb_record r;
            if (dw4_igb_decode(&g, off, &r)) {
                printf("  id %ld -> object +0x%x %s", g_ref_id, off, r.class_name);
                if (r.name)
                    printf(" name=%s", r.name);
                printf("\n");
                dw4_igb_record_free(&r);
            } else {
                printf("  id %ld -> object +0x%x (decode failed)\n", g_ref_id, off);
            }
        } else {
            printf("  id %ld -> unknown\n", g_ref_id);
        }
    }
    if (g_ref_list) {
        int shown = 0, want = g_ref_list > 0 ? g_ref_list : 40;
        for (i = 0; i < g.table_n && shown < want; i++) {
            if (g.id_kind[i] != 1)
                continue;
            printf("  id %-7u off +0x%-8x len %-8u ", i, g.id_off[i], g.id_len[i]);
            for (j = 0; j < g.id_len[i] && j < 12; j++)
                printf("%02x", g.data[g.id_off[i] + j]);
            printf("\n");
            shown++;
        }
    }
    dw4_igb_close(&g);
    return 0;
}


/* Resolve a manifest part name (the manifest spells them lower-case) against a
 * directory of the extracted archives (which are upper-case). */
static int open_part_archive(dw4_afs *a, const char *dir, const char *part)
{
    size_t i, n = strlen(part), d = strlen(dir);
    char *path = (char *)malloc(d + n + 2);
    int rc;

    if (!path)
        return -1;
    memcpy(path, dir, d);
    path[d] = '/';
    memcpy(path + d + 1, part, n + 1);
    rc = dw4_afs_open(a, path);
    if (rc == 0) {
        free(path);
        return 0;
    }
    for (i = 0; i < n; i++)
        path[d + 1 + i] = (char)toupper((unsigned char)part[i]);
    rc = dw4_afs_open(a, path);
    free(path);
    return rc;
}

static int cmd_manifest(const uint8_t *blob, size_t len, const char *label, int all)
{
    dw4_igb g;
    dw4_manifest m;
    uint32_t i;

    if (dw4_igb_open(&g, blob, len, 0) != 0 || dw4_manifest_open(&m, &g) != 0) {
        fprintf(stderr, "manifest: %s has no NDMW filesystem table\n", label);
        return 1;
    }
    if (all) {
        for (i = 0; i < m.nfiles; i++)
            printf("%s\t%d\t%d\n", m.files[i].name, m.files[i].pt, m.files[i].entry);
        dw4_manifest_close(&m);
        dw4_igb_close(&g);
        return 0;
    }
    printf("%s\n  %u archive part(s), %u named file(s)\n", label, m.nparts, m.nfiles);
    for (i = 0; i < m.nparts; i++)
        printf("    part %u  %-12s %d entries\n", i, m.parts[i].name, m.parts[i].file_count);
    for (i = 0; i < m.nfiles && i < 8; i++)
        printf("    %-28s pt=%d entry=%d\n", m.files[i].name, m.files[i].pt, m.files[i].entry);
    if (m.nfiles > 8)
        printf("    ... %u more\n", m.nfiles - 8);
    dw4_manifest_close(&m);
    dw4_igb_close(&g);
    return 0;
}

static int cmd_find(const char *manifest, const char *roms, const char *name,
                    const char *out)
{
    uint8_t *blob = NULL;
    size_t len = 0;
    dw4_igb g;
    dw4_manifest m;
    const dw4_manifest_file *f;
    const dw4_manifest_part *part;
    dw4_afs a;
    const uint8_t *data;
    FILE *o;

    if (read_file(manifest, &blob, &len) != 0) {
        fprintf(stderr, "find: cannot read %s\n", manifest);
        return 1;
    }
    if (dw4_igb_open(&g, blob, len, 0) != 0 || dw4_manifest_open(&m, &g) != 0) {
        fprintf(stderr, "find: %s is not a manifest\n", manifest);
        free(blob);
        return 1;
    }
    f = dw4_manifest_find(&m, name);
    if (!f) {
        fprintf(stderr, "find: %s is not in the manifest\n", name);
        dw4_manifest_close(&m);
        dw4_igb_close(&g);
        free(blob);
        return 1;
    }
    part = dw4_manifest_part_of(&m, f->pt);
    if (!part || f->entry < 0) {
        fprintf(stderr, "find: %s has no archive entry (pt=%d entry=%d)\n", name, f->pt,
                f->entry);
        dw4_manifest_close(&m);
        dw4_igb_close(&g);
        free(blob);
        return 1;
    }
    if (open_part_archive(&a, roms, part->name) != 0) {
        fprintf(stderr, "find: cannot open %s/%s\n", roms, part->name);
        dw4_manifest_close(&m);
        dw4_igb_close(&g);
        free(blob);
        return 1;
    }
    data = dw4_afs_entry_data(&a, (uint32_t)f->entry);
    if (!data) {
        fprintf(stderr, "find: %s -> %s entry %d is out of range\n", name, part->name,
                f->entry);
        dw4_afs_close(&a);
        dw4_manifest_close(&m);
        dw4_igb_close(&g);
        free(blob);
        return 1;
    }
    o = out ? fopen(out, "wb") : stdout;
    if (!o) {
        fprintf(stderr, "find: cannot write %s\n", out);
        dw4_afs_close(&a);
        dw4_manifest_close(&m);
        dw4_igb_close(&g);
        free(blob);
        return 1;
    }
    if (!out)
        fprintf(stderr, "find: %s -> %s entry %d (%u bytes)\n", name, part->name,
                f->entry, a.entries[f->entry].size);
    fwrite(data, 1, a.entries[f->entry].size, o);
    if (out) {
        fclose(o);
        printf("%s -> %s entry %d, %u bytes\n", name, part->name, f->entry,
               a.entries[f->entry].size);
    }
    dw4_afs_close(&a);
    dw4_manifest_close(&m);
    dw4_igb_close(&g);
    free(blob);
    return 0;
}


static int cmd_mount(const char *roms, const char *sub, const char *arg, const char *out)
{
    dw4_mount m;
    uint32_t i, bad = 0;

    if (dw4_mount_open(&m, roms) != 0)
        return 1;

    if (strcmp(sub, "ls") == 0) {
        for (i = 0; i < m.man.nfiles; i++) {
            const dw4_manifest_file *f = &m.man.files[i];
            const dw4_manifest_part *p = dw4_manifest_part_of(&m.man, f->pt);
            uint32_t sz = 0;
            if (arg && !strstr(f->name, arg))
                continue;
            dw4_mount_entry(&m, f->pt, f->entry, &sz, NULL);
            printf("%-30s %-10s %5d %9u\n", f->name, p ? p->name : "?", f->entry, sz);
        }
    } else if (strcmp(sub, "cat") == 0 && arg) {
        uint32_t sz = 0;
        const uint8_t *p = dw4_mount_data(&m, arg, &sz);
        FILE *o = out ? fopen(out, "wb") : stdout;
        if (!p || !o) {
            fprintf(stderr, "mount cat: cannot resolve %s\n", arg);
            if (o && out) fclose(o);
            dw4_mount_close(&m);
            return 1;
        }
        fwrite(p, 1, sz, o);
        if (out) {
            fclose(o);
            printf("%s: %u bytes -> %s\n", arg, sz, out);
        }
    } else if (strcmp(sub, "refs") == 0 && arg) {
        uint32_t sz = 0, n, j;
        const uint8_t *p = dw4_mount_data(&m, arg, &sz);
        dw4_ref refs[64];
        if (!p) {
            fprintf(stderr, "mount refs: cannot resolve %s\n", arg);
            dw4_mount_close(&m);
            return 1;
        }
        n = dw4_mount_scan_refs(p, sz, refs, 64);
        printf("%s: %u [pt.entry] reference(s)\n", arg, n);
        for (j = 0; j < n && j < 64; j++) {
            const dw4_manifest_part *part = dw4_manifest_part_of(&m.man, refs[j].pt);
            uint32_t esz = 0;
            const uint8_t *e = dw4_mount_entry(&m, refs[j].pt, refs[j].entry, &esz, NULL);
            printf("  [%d.%d] @0x%-6x -> %-10s entry %-6d %9u bytes%s\n", refs[j].pt,
                   refs[j].entry, refs[j].off, part ? part->name : "?", refs[j].entry, esz,
                   e ? "" : "  OUT OF RANGE");
        }
    } else if (strcmp(sub, "check") == 0) {
        for (i = 0; i < m.man.nfiles; i++) {
            const dw4_manifest_file *f = &m.man.files[i];
            if (!dw4_manifest_part_of(&m.man, f->pt) || f->entry < 0) {
                /* the manifest's own "NONE" record: a name with no archive entry */
                continue;
            }
            if (!dw4_mount_entry(&m, f->pt, f->entry, NULL, NULL)) {
                printf("  unresolved: %-28s pt=%d entry=%d\n", f->name, f->pt, f->entry);
                bad++;
            }
        }
        printf("%u named files with an entry, all resolve into their archive\n",
               m.man.nfiles - 1 - bad);
        if (bad)
            printf("  %u do NOT\n", bad);
    } else {
        fprintf(stderr, "mount needs ls|cat|refs|check\n");
        dw4_mount_close(&m);
        return 2;
    }
    dw4_mount_close(&m);
    return bad ? 1 : 0;
}


/* Which entries of the mounted archives contain a class?  A pack announces itself with an
 * igBinary directory, so this is a directory walk per entry, not a record decode. */
static int cmd_scan(const char *roms, const char *cls)
{
    dw4_mount m;
    int i;
    uint32_t e, total = 0;

    if (dw4_mount_open(&m, roms) != 0)
        return 1;
    for (i = 0; i < m.nparts; i++) {
        const dw4_manifest_part *part = dw4_manifest_part_of(&m.man, i);
        for (e = 0; e < m.parts[i].count; e++) {
            const uint8_t *p = dw4_afs_entry_data(&m.parts[i], e);
            dw4_igb g;
            if (!p || m.parts[i].entries[e].size < 0x30)
                continue;
            if (dw4_igb_open(&g, p, m.parts[i].entries[e].size, 0) != 0)
                continue;
            if (dw4_igb_find_class(&g, cls)) {
                /* count records of that class in the longest chain: a pack can declare a
                 * class and hold no instance of it (a directory-only pack) */
                uint32_t p2, n2 = 0;
                const char *nm = NULL;
                dw4_manifest_file *mf = NULL;
                uint32_t fi;
                /* every chain, not just the longest: object data and the in-memory
                 * directory are separate chains in a directory-style pack */
                for (p2 = 0x800; (size_t)p2 + 8 < g.size;) {
                    uint32_t end;
                    dw4_igb_record r;
                    if (!dw4_igb_record_end(&g, p2, &end)) {
                        p2 += 2;
                        continue;
                    }
                    if (dw4_igb_decode(&g, p2, &r)) {
                        if (strcmp(r.class_name, cls) == 0)
                            n2++;
                        dw4_igb_record_free(&r);
                    }
                    p2 = end;
                }
                for (fi = 0; fi < m.man.nfiles; fi++)
                    if (m.man.files[fi].pt == i && m.man.files[fi].entry == (int)e) {
                        mf = &m.man.files[fi];
                        nm = mf->name;
                    }
                printf("%-9s %5u %-22s %9u  %4u %-24s %u record(s)\n",
                       part ? part->name : "?", e, nm ? nm : "<unnamed>",
                       m.parts[i].entries[e].size, g.nclasses, cls, n2);
                total++;
            }
            dw4_igb_close(&g);
        }
    }
    printf("%u entr%s contain %s\n", total, total == 1 ? "y" : "ies", cls);
    dw4_mount_close(&m);
    return total ? 0 : 1;
}


/* Media export. Sofdec contains MPEG-1 video and ADX audio and ffmpeg reads it
 * directly. Standalone ADX music also lives in NDMW.AFS; resident sound effects
 * use the native ps2_ bank reader. See docs/audio-playback.md. */
static int cmd_media(const char *roms, const char *verb, const char *name, const char *out,
                     int argc, char **argv)
{
    dw4_mount m;
    uint32_t sz = 0;
    const uint8_t *p;
    char tmpl[] = "/tmp/dw4mediaXXXXXX";
    char cmd[4096];
    int fd, rc;

    if (dw4_mount_open(&m, roms) != 0)
        return 1;
    if (strcmp(verb, "list") == 0) {
        uint32_t i;
        for (i = 0; i < m.man.nfiles; i++) {
            const char *n = m.man.files[i].name;
            size_t l = strlen(n);
            if ((l > 4 && strcmp(n + l - 4, ".sfd") == 0) ||
                (l > 4 && strcmp(n + l - 4, ".adx") == 0))
                printf("%s\n", n);
        }
        dw4_mount_close(&m);
        return 0;
    }
    if (!name) {
        fprintf(stderr, "media needs list|probe|convert\n");
        dw4_mount_close(&m);
        return 2;
    }
    if (strchr(name, '\'') || (out && strchr(out, '\''))) {
        fprintf(stderr, "media: quote-unsafe name\n");
        dw4_mount_close(&m);
        return 2;
    }
    p = dw4_mount_data(&m, name, &sz);
    if (!p) {
        fprintf(stderr, "media: cannot resolve %s\n", name);
        dw4_mount_close(&m);
        return 1;
    }
    fd = mkstemp(tmpl);
    if (fd < 0) {
        dw4_mount_close(&m);
        return 1;
    }
    if (write(fd, p, sz) != (ssize_t)sz) {
        close(fd);
        dw4_mount_close(&m);
        return 1;
    }
    close(fd);
    if (strcmp(verb, "probe") == 0) {
        snprintf(cmd, sizeof(cmd), "ffprobe -hide_banner -i '%s'", tmpl);
    } else {
        int n = snprintf(cmd, sizeof(cmd),
                         "ffmpeg -y -hide_banner -loglevel error -i '%s'", tmpl);
        int i;
        for (i = 6; i < argc && n > 0 && (size_t)n < sizeof(cmd); i++)
            n += snprintf(cmd + n, sizeof(cmd) - (size_t)n, " %s", argv[i]);
        snprintf(cmd + n, sizeof(cmd) - (size_t)n, " '%s'", out);
    }
    printf("%s: %u bytes -> %s\n", name, sz, verb);
    rc = system(cmd);
    unlink(tmpl);
    dw4_mount_close(&m);
    return rc == 0 ? 0 : 1;
}


/* The stage sound packs.  A stage's `[0.620]` pack is an igBinary container whose
 * content pool holds six `ps2_DTPK` banks; each bank is VAG ADPCM and
 * decodes to a WAV.  The banks are listed by index; the pack's `beCriSfpData` records
 * name them (e_goburi.sfp, ...), and tools/verify_sound.py matches that name set.
 *
 *   dw4asset sfp <file>|--afs A --entry N                 list the banks
 *   dw4asset sfp ... [--bank K] [--sound S] --wav OUT     decode one bank (or one sound)
 */
static int cmd_sfp(const uint8_t *blob, size_t len, const char *label, int argc, char **argv)
{
    dw4_sfp_bank banks[64];
    dw4_sfp_sound sounds[1024];
    dw4_igb g;
    int have_g;
    uint32_t nb, ns = 0, i;
    int bank = -1, sound = -1;
    const char *wav = NULL, *name = NULL;
    int k;

    for (k = 2; k < argc; k++) {
        if (strcmp(argv[k], "--bank") == 0 && k + 1 < argc)
            bank = (int)strtol(argv[++k], NULL, 0);
        else if (strcmp(argv[k], "--sound") == 0 && k + 1 < argc)
            sound = (int)strtol(argv[++k], NULL, 0);
        else if (strcmp(argv[k], "--name") == 0 && k + 1 < argc)
            name = argv[++k];
        else if (strcmp(argv[k], "--wav") == 0 && k + 1 < argc)
            wav = argv[++k];
    }

    nb = dw4_sfp_scan(blob, len, banks, 64);
    if (!nb) {
        fprintf(stderr, "sfp: no ps2_DTPK banks in %s\n", label);
        return 1;
    }
    /* The pack's own records name the banks and the sounds; an entry-620-shaped pack
     * always opens, and a bare bank blob may not (then names are simply absent). */
    have_g = dw4_igb_open(&g, blob, len, 0) == 0;
    if (have_g) {
        dw4_sfp_bank_names(&g, banks, nb);
        ns = dw4_sfp_sounds(&g, banks, nb, sounds, 1024);
    }

    if (name) {
        for (i = 0; i < ns && i < 1024; i++)
            if (strcmp(sounds[i].name, name) == 0 && sounds[i].bank >= 0) {
                bank = sounds[i].bank;
                sound = (int)sounds[i].entry;
                break;
            }
        if (bank < 0) {
            fprintf(stderr, "sfp: no sound named '%s' in %s\n", name, label);
            if (have_g)
                dw4_igb_close(&g);
            return 1;
        }
    }

    if (!wav) {
        printf("%s: %u sound bank(s)", label, nb);
        if (have_g)
            printf(", %u named sound(s)", ns);
        printf("\n");
        for (i = 0; i < nb && i < 64; i++) {
            dw4_sfp_entry ents[128];
            uint32_t ne = dw4_sfp_entries(blob, len, &banks[i], ents, 128), e, s;
            printf("  bank %u @0x%06x  %-18s pcm %-7u vag %-7u rate %-6u entries %u\n",
                   i, banks[i].off, banks[i].name[0] ? banks[i].name : "<unnamed>",
                   banks[i].pcm_size, banks[i].vag_size, banks[i].rate, ne);
            for (e = 0; e < ne && e < 128; e++) {
                const char *nm = NULL;
                for (s = 0; s < ns && s < 1024; s++)
                    if (sounds[s].bank == (int)i && sounds[s].entry == e) { nm = sounds[s].name; break; }
                printf("      entry %-2u %s\n", e, nm ? nm : "<unnamed>");
            }
        }
        if (have_g)
            dw4_igb_close(&g);
        return 0;
    }

    if (bank < 0 || (uint32_t)bank >= nb) {
        fprintf(stderr, "sfp: --bank K out of range (0..%u)\n", nb ? nb - 1 : 0);
        if (have_g)
            dw4_igb_close(&g);
        return 1;
    }
    {
        const dw4_sfp_bank *b = &banks[bank];
        uint32_t start = 0, bytes = b->vag_size;
        size_t frames, cap, got;
        int16_t *pcm;

        if (sound >= 0) {
            dw4_sfp_entry ents[128];
            uint32_t ne = dw4_sfp_entries(blob, len, b, ents, 128);
            if ((uint32_t)sound >= ne) {
                fprintf(stderr, "sfp: --sound S out of range (0..%u)\n", ne ? ne - 1 : 0);
                if (have_g)
                    dw4_igb_close(&g);
                return 1;
            }
            start = ents[sound].start - 0x20;   /* entry offsets include the VAGD header */
            bytes = ents[sound].end - ents[sound].start;
        }
        frames = bytes / 16;
        cap = frames * 28 + 28;
        pcm = (int16_t *)malloc(cap * sizeof(*pcm));
        if (!pcm) {
            if (have_g)
                dw4_igb_close(&g);
            return 1;
        }
        got = dw4_vag_decode(blob + b->vag_data + start, (size_t)bytes, pcm, cap);
        if (dw4_wav_write(wav, pcm, got, b->rate) != 0) {
            fprintf(stderr, "sfp: cannot write %s\n", wav);
            free(pcm);
            if (have_g)
                dw4_igb_close(&g);
            return 1;
        }
        printf("%s: %s (bank %d entry %d) -> %s  %zu samples @ %u Hz (%.2f s)\n", label,
               name ? name : (b->name[0] ? b->name : "bank"), bank, sound, wav, got, b->rate,
               b->rate ? (double)got / b->rate : 0.0);
        free(pcm);
    }
    if (have_g)
        dw4_igb_close(&g);
    return 0;
}

/* Decode an indexed texture from explicit inputs.  The buffers cannot be located
 * offline yet (a memory ref is a load-time ordinal), so the CLI takes
 * the index and palette bytes directly: the decode half is what the renderer needs,
 * and it is testable on its own (tools/verify_texture.py). */
static int cmd_texture(const char *src_path, const char *png_path, int argc, char **argv)
{
    uint8_t *src = NULL, *pal = NULL, *rgba;
    size_t src_len = 0, pal_len = 0;
    uint32_t w = 0, h = 0, bpr = 0, pal_entries = 0;
    int bits = 8, i, flip = 0;
    dw4_pal_mode mode = DW4_PAL_RGBA8888;
    const char *pal_path = NULL;

    for (i = 3; i < argc; i++) {
        if (strcmp(argv[i], "--w") == 0 && i + 1 < argc)
            w = (uint32_t)strtoul(argv[++i], NULL, 0);
        else if (strcmp(argv[i], "--h") == 0 && i + 1 < argc)
            h = (uint32_t)strtoul(argv[++i], NULL, 0);
        else if (strcmp(argv[i], "--bits") == 0 && i + 1 < argc)
            bits = (int)strtoul(argv[++i], NULL, 0);
        else if (strcmp(argv[i], "--bpr") == 0 && i + 1 < argc)
            bpr = (uint32_t)strtoul(argv[++i], NULL, 0);
        else if (strcmp(argv[i], "--pal") == 0 && i + 1 < argc)
            pal_path = argv[++i];
        else if (strcmp(argv[i], "--pal-entries") == 0 && i + 1 < argc)
            pal_entries = (uint32_t)strtoul(argv[++i], NULL, 0);
        else if (strcmp(argv[i], "--flip") == 0)
            flip = 1;
        else if (strcmp(argv[i], "--pal-mode") == 0 && i + 1 < argc) {
            const char *m = argv[++i];
            mode = strcmp(m, "ps2csm1") == 0 ? DW4_PAL_PS2_CSM1 : DW4_PAL_RGBA8888;
        }
    }
    if (!pal_path || !w || !h) {
        fprintf(stderr, "texture needs <src.raw> <out.png> --w W --h H --pal <pal.raw>\n"
                        "  [--bits 8|4] [--bpr N] [--pal-entries N]"
                        " [--pal-mode rgba8888|ps2csm1]\n");
        return 2;
    }
    if (read_file(src_path, &src, &src_len) != 0 || read_file(pal_path, &pal, &pal_len) != 0) {
        fprintf(stderr, "texture: cannot read inputs\n");
        free(src);
        free(pal);
        return 1;
    }
    if (!pal_entries)
        pal_entries = mode == DW4_PAL_PS2_CSM1 ? (uint32_t)(pal_len / 2)
                                               : (uint32_t)(pal_len / 4);
    if (!bpr)
        bpr = (w * (uint32_t)bits + 7) / 8;
    rgba = (uint8_t *)malloc((size_t)w * h * 4);
    if (!rgba) {
        free(src);
        free(pal);
        return 1;
    }
    if (dw4_texture_rgba(src, (uint32_t)src_len, w, h, bits, bpr, pal, (uint32_t)pal_len,
                         pal_entries, mode, rgba) != 0) {
        fprintf(stderr, "texture: the inputs do not cover %ux%u at %d bits"
                        " (need %u bytes of indices, have %zu; %u palette entries"
                        " of %s)\n", w, h, bits, bpr * h, src_len, pal_entries,
                mode == DW4_PAL_PS2_CSM1 ? "2 bytes" : "4 bytes");
        free(rgba);
        free(src);
        free(pal);
        return 1;
    }
    if (flip) {
        /* PS2 textures are stored bottom-up; the reference atlas reads correctly only
         * after a vertical flip */
        uint32_t y;
        for (y = 0; y < h / 2; y++) {
            uint8_t *a = rgba + (size_t)y * w * 4;
            uint8_t *b = rgba + (size_t)(h - 1 - y) * w * 4;
            uint32_t k;
            for (k = 0; k < w * 4; k++) {
                uint8_t tmp = a[k];
                a[k] = b[k];
                b[k] = tmp;
            }
        }
    }
    if (dw4_png_write(png_path, rgba, w, h) != 0) {
        fprintf(stderr, "texture: cannot write %s\n", png_path);
        free(rgba);
        free(src);
        free(pal);
        return 1;
    }
    printf("%s: %ux%u, %d bits, bpr %u, %u palette entries (%s)%s -> %s\n", src_path, w, h,
           bits, bpr, pal_entries, mode == DW4_PAL_PS2_CSM1 ? "ps2csm1" : "rgba8888",
           flip ? ", flipped" : "", png_path);
    free(rgba);
    free(src);
    free(pal);
    return 0;
}

/* Textures from a live EE RAM dump (`livetex.c`): list every named `igPsx2Image`, or decode
 * one to a PNG.  This is the source the pack path cannot reach for a character/world material
 * -- the live graph points at ordinary pointers.
 *
 *   dw4asset livetex <ram.bin> --list
 *   dw4asset livetex <ram.bin> --decode E_ogre01.png --out ogre.png
 */
static int cmd_livetex(int argc, char **argv)
{
    dw4_livetex *lt;
    const char *decode = NULL, *out = NULL;
    int i, rc = 0;

    if (argc < 1) {
        fprintf(stderr, "usage: dw4asset livetex <ram.bin> [--list] [--decode NAME --out F.png]\n");
        return 2;
    }
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--decode") == 0 && i + 1 < argc)
            decode = argv[++i];
        else if (strcmp(argv[i], "--out") == 0 && i + 1 < argc)
            out = argv[++i];
    }
    lt = dw4_livetex_open(argv[0]);
    if (!lt) {
        fprintf(stderr, "livetex: %s is not a 31/32 MB EE RAM image\n", argv[0]);
        return 1;
    }
    printf("%s: %d named texture(s)\n", argv[0], dw4_livetex_count(lt));
    if (decode) {
        uint8_t *rgba = NULL;
        int w = 0, h = 0;
        if (dw4_livetex_get(lt, decode, &rgba, &w, &h) != 0) {
            fprintf(stderr, "livetex: no %s in %s\n", decode, argv[0]);
            dw4_livetex_close(lt);
            return 1;
        }
        if (!out)
            out = "livetex.png";
        if (dw4_png_write(out, rgba, w, h) != 0) {
            fprintf(stderr, "livetex: cannot write %s\n", out);
            rc = 1;
        } else {
            printf("  %s: %dx%d -> %s\n", decode, w, h, out);
        }
        free(rgba);
    } else {
        for (i = 0; i < dw4_livetex_count(lt); i++)
            printf("  %s\n", dw4_livetex_name(lt, i));
    }
    dw4_livetex_close(lt);
    return rc;
}

/* A skinned character mesh from the same kind of dump: the runtime blend stream, the bone map
 * and the matrix palette, skinned in C.  This is the counterpart of
 * `scripts/live_skin.py`; `tools/verify_skin.py` diffs the two OBJs. */
static int cmd_skin(int argc, char **argv)
{
    const char *out = NULL, *bind = NULL, *ram = NULL;
    int palette = -1, list = 0, i, rc = 0;

    if (argc < 1) {
        fprintf(stderr, "usage: dw4asset skin <ram.bin> [--list] [--palette N] "
                        "[--out F.obj] [--bind F.obj]\n");
        return 2;
    }
    for (i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--out") == 0 && i + 1 < argc)
            out = argv[++i];
        else if (strcmp(argv[i], "--bind") == 0 && i + 1 < argc)
            bind = argv[++i];
        else if (strcmp(argv[i], "--palette") == 0 && i + 1 < argc)
            palette = atoi(argv[++i]);
        else if (strcmp(argv[i], "--list") == 0)
            list = 1;
        else if (argv[i][0] != '-')
            ram = argv[i];
    }
    if (!ram) {
        fprintf(stderr, "skin: no RAM dump given\n");
        return 2;
    }
    {
        dw4_skin *sk = dw4_skin_open(ram);
        if (!sk) {
            fprintf(stderr, "skin: %s has no live skinned mesh\n", ram);
            return 1;
        }
        dw4_skin_print(sk);
        if (!list) {
            if (palette < 0)
                palette = dw4_skin_default_palette(sk);
            printf("  using palette[%d] %08x (%d matrices)\n",
                   palette, dw4_skin_palette_addr(sk, palette),
                   dw4_skin_palette_size(sk, palette));
            if (bind && dw4_skin_write_obj(sk, palette, bind, 0) != 0) {
                fprintf(stderr, "skin: cannot write %s\n", bind);
                rc = 1;
            }
            if (out && dw4_skin_write_obj(sk, palette, out, 1) != 0) {
                fprintf(stderr, "skin: cannot write %s\n", out);
                rc = 1;
            }
        }
        dw4_skin_close(sk);
    }
    return rc;
}

/* A texture pack read end to end: the pool layout, the id->class table and the
 * image -> palette link.  Nothing here needs a load replay,
 * so this is the offline texture loader the renderer consumes. */
static int cmd_texpack(const uint8_t *blob, size_t len, const char *label, int argc,
                       char **argv)
{
    dw4_texpack tp;
    const char *decode = NULL, *out = NULL;
    int list = 0, i, rc = 0;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--list") == 0)
            list = 1;
        else if (strcmp(argv[i], "--decode") == 0 && i + 1 < argc)
            decode = argv[++i];
        else if (strcmp(argv[i], "--out") == 0 && i + 1 < argc)
            out = argv[++i];
    }
    if (dw4_texpack_open(&tp, blob, len) != 0) {
        fprintf(stderr, "texpack: %s is not a texture pack this reader understands"
                        " (the header must describe the pool and the id->class table"
                        " must validate)\n", label);
        return 1;
    }
    printf("%s: %u clut + %u image blocks + %u pad, pool 0x%x .. 0x%x;"
           " id table @0x%x, %u ids (block class %u, object class %u), %u textures\n",
           label, tp.nclut, tp.nimg, tp.npad, tp.pool_base, tp.pool_end, tp.tbl_off,
           tp.tbl_count, tp.block_class, tp.obj_class, tp.ntex);

    if (decode) {
        const dw4_texpack_tex *t = dw4_texpack_find(&tp, decode);
        uint8_t *rgba;
        size_t n;
        if (!t) {
            fprintf(stderr, "texpack: no texture %s\n", decode);
            return 1;
        }
        rgba = (uint8_t *)malloc((size_t)t->w * t->h * 4);
        if (!rgba)
            return 1;
        if (dw4_texpack_rgba(&tp, t->image_id, t->clut_id, rgba) != 0) {
            fprintf(stderr, "texpack: cannot decode %s (ids out of the layout)\n", decode);
            free(rgba);
            return 1;
        }
        n = (size_t)t->w * t->h * 4;
        if (out && strlen(out) > 4 && strcmp(out + strlen(out) - 4, ".png") == 0)
            rc = dw4_png_write(out, rgba, t->w, t->h);
        else {
            FILE *f = out ? fopen(out, "wb") : stdout;
            if (!f)
                rc = -1;
            else {
                rc = (fwrite(rgba, 1, n, f) == n) ? 0 : -1;
                if (out)
                    fclose(f);
            }
        }
        printf("  %s %ux%u image id %u palette id %u -> %s%s\n", t->name, t->w, t->h,
               t->image_id, t->clut_id, rc == 0 ? "ok" : "FAILED",
               out ? out : " (stdout)");
        free(rgba);
        dw4_texpack_close(&tp);
        return rc == 0 ? 0 : 1;
    }
    if (list) {
        for (i = 0; i < (int)tp.ntex; i++) {
            const dw4_texpack_tex *t = &tp.tex[i];
            printf("  %-18s %4ux%-4u image id %-4u 0x%-6x (grid) palette id %-4u 0x%-6x\n",
                   t->name, t->w, t->h, t->image_id, t->grid_off, t->clut_id,
                   t->pal_off);
        }
    }
    dw4_texpack_close(&tp);
    return 0;
}

static int cmd_models(const uint8_t *blob, size_t len, const char *label, int argc, char **argv)
{
    dw4_models ms;
    const char *out_dir = NULL, *out = NULL;
    long want = -1, limit = -1;
    int tsv = 0, list = 0, i, ok = 0, bad = 0, rc = 0;
    uint32_t nb = 0, region;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--list") == 0)
            list = 1;
        else if (strcmp(argv[i], "--tsv") == 0)
            tsv = 1;
        else if (strcmp(argv[i], "--out-dir") == 0 && i + 1 < argc)
            out_dir = argv[++i];
        else if (strcmp(argv[i], "--out") == 0 && i + 1 < argc)
            out = argv[++i];
        else if (strcmp(argv[i], "--obj") == 0 && i + 1 < argc)
            want = strtol(argv[++i], NULL, 0);
        else if (strcmp(argv[i], "--limit") == 0 && i + 1 < argc)
            limit = strtol(argv[++i], NULL, 0);
    }
    if (dw4_models_open(&ms, blob, len) != 0) {
        fprintf(stderr, "models: %s is not a model pack (an igBinary container with an id"
                        " remap table is required)\n", label);
        return 1;
    }
    for (i = 0; i < (int)ms.igb.table_n; i++)
        if (ms.igb.id_kind[i] == 1)
            nb++;
    region = (uint32_t)(ms.igb.size - ms.igb.pool_off);
    if (ms.igb.pool_sum == region)
        printf("pool @+0x%x, %u bytes; %u blocks, exact after 4-byte alignment\n",
               ms.pool_off, region, nb);
    else
        printf("pool @+0x%x, %u bytes; %u blocks, short by %u\n", ms.pool_off, region, nb,
               region - ms.igb.pool_sum);
    printf("geometry attributes: %u\n", ms.n);

    if (tsv) {
        for (i = 0; i < (int)ms.n; i++) {
            uint32_t ids[32];
            uint32_t k, ns = dw4_models_streams(&ms, ms.m[i].vdata, ids, 32);
            printf("%u\t%u\t%u\t%u\t%u\t%u\t", ms.m[i].vertex_array, ms.m[i].prim_type,
                   ms.m[i].num_prims, ms.m[i].num_verts, ms.m[i].vdata, ms.m[i].num_lengths);
            for (k = 0; k < ns && k < 32; k++)
                printf("%s%u", k ? "," : "", ids[k]);
            printf("\t%s\n", ms.m[i].name ? ms.m[i].name : "");
        }
        dw4_models_close(&ms);
        return 0;
    }
    if (list) {
        for (i = 0; i < (int)ms.n && (limit < 0 || i < limit); i++) {
            uint32_t ids[32];
            uint32_t k, ns = dw4_models_streams(&ms, ms.m[i].vdata, ids, 32);
            printf("  %3d  vertexArray %-7u primType %u numPrims %-5u numVerts %-5u %-22s streams [",
                   i, ms.m[i].vertex_array, ms.m[i].prim_type, ms.m[i].num_prims,
                   ms.m[i].num_verts, ms.m[i].name ? ms.m[i].name : "-");
            for (k = 0; k < ns && k < 32; k++)
                printf("%s%u", k ? ", " : "", ids[k]);
            printf("]\n");
        }
        dw4_models_close(&ms);
        return 0;
    }

    for (i = 0; i < (int)ms.n; i++) {
        const dw4_model *g = &ms.m[i];
        const char *why = NULL;
        uint32_t *tris = NULL, ntris = 0;
        char path[4096], base[256];
        FILE *f;

        if (want >= 0 && (long)g->vertex_array != want)
            continue;
        if (limit >= 0 && ok + bad >= limit)
            break;
        if (dw4_models_tris(&ms, g, &tris, &ntris, &why) != 0) {
            bad++;
            fprintf(stderr, "  %3d  vertexArray %-7u SKIP (%s)\n", i, g->vertex_array, why);
            continue;
        }
        free(tris);
        ok++;
        if (!out_dir) {
            printf("  %3d  vertexArray %-7u %-22s %u verts, %u prims, %u tris\n", i,
                   g->vertex_array, g->name ? g->name : "-", g->num_verts, g->num_prims,
                   ntris);
            continue;
        }
        dw4_models_obj_basename(g, base, sizeof(base));
        snprintf(path, sizeof(path), "%s/%s", out_dir, base);
        f = fopen(path, "wb");
        if (!f || dw4_models_write_obj(&ms, g, f) != 0) {
            fprintf(stderr, "models: cannot write %s\n", path);
            if (f)
                fclose(f);
            rc = 1;
            continue;
        }
        fclose(f);
        if (out && want >= 0) {
            f = fopen(out, "wb");
            if (f && dw4_models_write_obj(&ms, g, f) == 0) {
                printf("  wrote %s: %u verts, %u prims, %u tris (vertexArray id %u)\n", out,
                       g->num_verts, g->num_prims, ntris, g->vertex_array);
            } else {
                fprintf(stderr, "models: cannot write %s\n", out);
                rc = 1;
            }
            if (f)
                fclose(f);
        }
    }
    if (want >= 0 && !ok && !bad) {
        fprintf(stderr, "models: no geometry attribute with _vertexArray id %ld\n", want);
        rc = 1;
    }
    if (!out) {
        if (out_dir)
            printf("extracted %d, skipped %d -> %s\n", ok, bad, out_dir);
        else if (want < 0)
            printf("extracted %d, skipped %d\n", ok, bad);
    }
    dw4_models_close(&ms);
    return rc;
}

/* --- the scene loader: a pack in the guest arena, handed out as renderer-ready meshes -------
 *
 *   dw4asset scene <roms-dir> <name.igb>     the engine-shaped route (manifest -> archive)
 *   dw4asset scene --afs A --entry N         one archive entry
 *   dw4asset scene <file>                    a file on disk
 *
 * `--check` validates the loader's own output (the ids tile the arena and every payload is the
 * file's bytes, every mesh handle resolves), which is what `tools/verify_scene.py` asserts. */
/* dw4asset chr <roms-dir> --t SECONDS [--sel N] [--out F.png]: the Game Start slot screen at one clock
 * (every layer on the same time), for calibrating `src/frontchr.c` against retail captures. */
static int cmd_chr(int argc, char **argv)
{
    dw4_mount mnt;
    dw4_frontchr *c;
    dw4_fefont font;
    dw4_fb fb;
    const char *out = "chr.png";
    int i, sel = 0, species = -1;

    if (argc < 1 || dw4_mount_open(&mnt, argv[0]) != 0) {
        fprintf(stderr, "usage: dw4asset chr <roms-dir> [--t SECONDS] [--sel N] [--species 0..3] [--out F.png]\n");
        return 2;
    }
    for (i = 1; i + 1 < argc; i++) {
        if (strcmp(argv[i], "--t") == 0)
            setenv("DW4_CHR_T", argv[++i], 1);
        else if (strcmp(argv[i], "--sel") == 0)
            sel = atoi(argv[++i]);
        else if (strcmp(argv[i], "--species") == 0)
            species = atoi(argv[++i]);
        else if (strcmp(argv[i], "--out") == 0)
            out = argv[++i];
    }
    c = dw4_frontchr_open(&mnt);
    if (!c || dw4_fb_init(&fb, 640, 448) != 0) {
        fprintf(stderr, "chr: cannot open the slot screen\n");
        return 1;
    }
    dw4_fb_clear(&fb, 24, 28, 36);
    memset(&font, 0, sizeof font);
    if (dw4_fefont_load(&font, argv[0]) != 0)
        fprintf(stderr, "chr: no front-end font; drawing without text\n");
    dw4_frontchr_species(c, species);
    dw4_frontchr_draw(c, &fb, sel, &font);
    dw4_png_write(out, fb.rgba, (uint32_t)fb.w, (uint32_t)fb.h);
    printf("chr -> %s\n", out);
    dw4_frontchr_close(c);
    return 0;
}

static int cmd_scene(int argc, char **argv)
{
    dw4_igfile f;
    dw4_scene sc;
    dw4_mount mnt;
    uint8_t *blob = NULL;
    size_t len = 0, total = 0;
    const char *out_dir = NULL, *arena_out = NULL;
    const char *cam_node = NULL;
    int list = 0, tsv = 0, check = 0, graph = 0, cam = 0, chain = 0, world_tsv = 0, have = 0, have_mount = 0, i, rc = 0;
    uint32_t j;
    const char *chain_name = NULL;
    double time_ns = 0.0;

    memset(&f, 0, sizeof(f));
    memset(&mnt, 0, sizeof(mnt));
    for (i = 0; i < argc; i++) {          /* argv[0] is the first arg: main passes argv + 2 */
        if (strcmp(argv[i], "--list") == 0)
            list = 1;
        else if (strcmp(argv[i], "--tsv") == 0)
            tsv = 1;
        else if (strcmp(argv[i], "--chain") == 0 && i + 1 < argc)
            chain = 1, chain_name = argv[++i];   /* print one node's ancestor chain + matrices */
        else if (strcmp(argv[i], "--time") == 0 && i + 1 < argc)
            time_ns = strtod(argv[++i], NULL);   /* evaluate the animated nodes at this instant */
        else if (strcmp(argv[i], "--world-tsv") == 0)
            world_tsv = 1;                       /* emit a `render --scene` capture from the graph */
        else if (strcmp(argv[i], "--check") == 0)
            check = 1;
        else if (strcmp(argv[i], "--graph") == 0)
            graph = 1;
        else if (strcmp(argv[i], "--cam") == 0)
            cam = 1;
        else if (strcmp(argv[i], "--cam-node") == 0 && i + 1 < argc)
            cam_node = argv[++i];
        else if (strcmp(argv[i], "--out-dir") == 0 && i + 1 < argc)
            out_dir = argv[++i];
        else if (strcmp(argv[i], "--arena-out") == 0 && i + 1 < argc)
            arena_out = argv[++i];
        else if (strcmp(argv[i], "--stage") == 0 && i + 3 < argc) {
            /* --stage <roms-dir> <stage.igb> --ref N : the engine's own route */
            const char *roms = argv[++i], *stage = argv[++i];
            uint32_t idx = 0;
            if (i + 1 < argc && strcmp(argv[i + 1], "--ref") == 0 && i + 2 < argc) {
                idx = (uint32_t)strtoul(argv[i + 2], NULL, 0);
                i += 2;
            }
            if (dw4_mount_open(&mnt, roms) != 0) {
                fprintf(stderr, "scene: cannot mount %s\n", roms);
                return 1;
            }
            have_mount = 1;
            if (dw4_igfile_open_stage_ref(&f, &mnt, stage, idx) != 0)
                return 1;
            have = 1;
        }
        else if (strcmp(argv[i], "--afs") == 0 && i + 1 < argc) {
            const char *path = argv[++i];
            if (i + 1 < argc && strcmp(argv[i + 1], "--entry") == 0 && i + 2 < argc) {
                uint32_t entry = (uint32_t)strtoul(argv[i + 2], NULL, 0);
                i += 2;
                if (dw4_igfile_open_afs(&f, path, entry) != 0)
                    return 1;
                have = 1;
            } else {
                fprintf(stderr, "scene: --afs needs --entry N\n");
                return 2;
            }
        } else if (argv[i][0] != '-' && !have) {
            /* one operand: either a mounted name (with a roms dir before it) or a file */
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                if (dw4_mount_open(&mnt, argv[i]) != 0) {
                    fprintf(stderr, "scene: cannot mount %s\n", argv[i]);
                    return 1;
                }
                have_mount = 1;
                if (dw4_igfile_open_named(&f, &mnt, argv[i + 1]) != 0)
                    return 1;
                i++;
            } else if (dw4_igfile_open_path(&f, argv[i]) != 0) {
                return 1;
            }
            have = 1;
        }
    }
    if (!have) {
        fprintf(stderr, "usage: dw4asset scene <roms-dir> <name>|--afs A --entry N|<file>"
                        "|--stage R <stage.igb> [--ref N] [--list|--tsv] [--out-dir D]"
                        " [--arena-out F] [--check] [--graph] [--cam|--cam-node NAME]\n");
        return 2;
    }
    blob = (uint8_t *)dw4_igfile_data(&f);
    len = dw4_igfile_size(&f);
    if (dw4_scene_load(&sc, blob, len) != 0) {
        fprintf(stderr, "scene: %s is not a loadable pack\n", f.name[0] ? f.name : f.path);
        rc = 1;
        goto done;
    }
    printf("scene %s: arena %u bytes, %u block(s) + %u object(s) = %u ids, %u mesh(es)\n",
           f.name[0] ? f.name : f.path, (uint32_t)sc.arena_len, sc.nblock, sc.nobject,
           sc.nent, sc.nmesh);
    dw4_scene_set_time(&sc, time_ns);    /* the animated nodes evaluate at this instant */

    if (check) {
        /* The loader's own contract: every id is placed exactly once, in order, and its payload is
         * the file's bytes for that id; every mesh handle lands inside the arena. */
        dw4_igb g;
        uint32_t off = DW4_SCENE_BASE, unplaced = 0, bad = 0;
        int have_igb = dw4_igb_open(&g, blob, len, 0) == 0 && dw4_igb_refs_open(&g) == 0;

        for (j = 0; j < sc.nent; j++) {
            const dw4_scene_ent *e = dw4_scene_lookup(&sc, j);
            const uint8_t *p = (const uint8_t *)dw4_scene_host(&sc, e->h);
            if (!p || e->h.off != off) {
                unplaced++;
                continue;
            }
            if (have_igb && e->kind == 1 && (e->size != g.id_len[j] ||
                                             memcmp(p, blob + g.id_off[j], e->size) != 0))
                bad++;                    /* only blocks: object records are rewritten on purpose */
            off += (e->size + (DW4_SCENE_ALIGN - 1)) & ~(DW4_SCENE_ALIGN - 1);
        }
        for (j = 0; j < sc.nmesh; j++) {
            const dw4_scene_mesh *g2 = &sc.mesh[j];
            if (!dw4_scene_host(&sc, g2->positions) ||
                (g2->uvs.off && !dw4_scene_host(&sc, g2->uvs)) ||
                (g2->lengths.off && !dw4_scene_host(&sc, g2->lengths)))
                bad++;
            total += g2->num_verts;
        }
        if (have_igb)
            dw4_igb_close(&g);
        printf("  check: %u id(s) placed in order, %u payload(s) differ from the file,"
               " %u mesh handle(s) broken, %u vertices\n", sc.nent, bad, unplaced,
               (uint32_t)total);
        printf("  id->pointer: %u reference(s) rewritten, %u NULL, %u NEITHER (must be 0)\n",
               sc.nref, sc.nnull, sc.nref_bad);
        if (unplaced || bad || !have_igb || sc.nref_bad) {
            rc = 1;
            goto done;
        }
    }
    if (arena_out) {
        FILE *fp = fopen(arena_out, "wb");
        if (!fp || fwrite(sc.arena, 1, sc.arena_len, fp) != sc.arena_len) {
            fprintf(stderr, "scene: cannot write %s\n", arena_out);
            if (fp)
                fclose(fp);
            rc = 1;
            goto done;
        }
        fclose(fp);
        printf("  wrote %s (%u bytes)\n", arena_out, (uint32_t)sc.arena_len);
    }
    if (cam || cam_node) {
        /* The stage's own camera (porting P4.2/P4.3): a camera node's
         * **world** matrix is its ancestor chain composed child x parent, and the view matrix is
         * that world's affine inverse.  `--cam` reports the stage camera (the first camera whose
         * composed world is not the identity) and every candidate; `--cam-node NAME` reports one. */
        float swm[16], sview[16];
        int sel = dw4_scene_camera(&sc, cam_node, swm, sview);
        uint32_t k;

        if (sel < 0) {
            printf("stage camera: none\n");
            rc = 1;
            goto done;
        }
        printf("stage camera: %-22s node %d depth %u  world pos (%8.3f %8.3f %8.3f)\n",
               sc.node[sel].name ? sc.node[sel].name : "-", sel, sc.node[sel].depth,
               (double)swm[12], (double)swm[13], (double)swm[14]);
        if (!cam_node) {
            /* list every igCamera so the chosen one can be audited */
            for (j = 0; j < sc.nnode; j++) {
                float wm[16];
                if (!sc.node[j].class_name || strcmp(sc.node[j].class_name, "igCamera") != 0)
                    continue;
                dw4_scene_node_camera(&sc, j, wm, NULL);
                printf("  camera %c %-22s node %3u depth %u  world pos (%8.3f %8.3f %8.3f)\n",
                       (int)j == sel ? '*' : ' ', sc.node[j].name ? sc.node[j].name : "-", j,
                       sc.node[j].depth, (double)wm[12], (double)wm[13], (double)wm[14]);
            }
        } else {
            /* the selected node's own chain and matrices */
            uint32_t chain[64], nc = 0;
            for (k = (uint32_t)sel; k != 0xFFFFFFFFu && nc < 64; k = sc.node[k].parent)
                chain[nc++] = k;
            printf("chain:");
            for (k = 0; k < nc; k++) {
                const dw4_scene_node *nd = &sc.node[chain[nc - 1 - k]];
                uint32_t t3;
                printf(" %s[", nd->class_name ? nd->class_name : "?");
                for (t3 = 0; t3 < 16; t3++)
                    printf("%s%.5f", t3 ? "," : "",
                           (double)(nd->has_matrix ? nd->m[t3] : (t3 % 5 == 0 ? 1.0f : 0.0f)));
                printf("]");
            }
            printf("\n");
        }
        printf("  world  ");
        for (k = 0; k < 16; k++)
            printf("%9.4f%s", (double)swm[k], (k % 4 == 3) ? "\n  m      " : " ");
        printf("\n  view   ");
        for (k = 0; k < 16; k++)
            printf("%9.4f%s", (double)sview[k], (k % 4 == 3) ? (k == 15 ? "\n" : "\n  v      ") : " ");
        printf("\n");
        rc = 0;
        goto done;
    }
    if (graph) {
        /* The scene graph (porting P4.2): what the stage's scenes name and where their nodes sit. */
        printf("  %u scene(s), %u node(s)\n", sc.ngraph, sc.nnode);
        for (j = 0; j < sc.ngraph; j++) {
            const dw4_scene_graph *gr = &sc.graph[j];
            printf("  scene %u %-20s %u node(s)\n", j, gr->name ? gr->name : "-", gr->nnodes);
        }
        for (j = 0; j < sc.nnode; j++) {
            const dw4_scene_node *n = &sc.node[j];
            const char *sysname = sc.node[0].class_name;
            (void)sysname;
            printf("  %4u %2u %-22s %-24s", j, n->depth, n->class_name ? n->class_name : "-", n->name ? n->name : "-");
            if (n->has_matrix) {
                /* A zero row in the 3x3 is a degenerate transform (composing it poisons descendants). */
                int bad = (n->m[0] == 0.0f && n->m[1] == 0.0f && n->m[2] == 0.0f) ||
                          (n->m[4] == 0.0f && n->m[5] == 0.0f && n->m[6] == 0.0f) ||
                          (n->m[8] == 0.0f && n->m[9] == 0.0f && n->m[10] == 0.0f);
                printf(" m[12..14] %8.3f %8.3f %8.3f%s", (double)n->m[12], (double)n->m[13],
                       (double)n->m[14], bad ? " !DEGEN" : "");
            } else
                printf(" %24s", "");
            if (n->geometry.off)
                printf("  geom +0x%x", n->geometry.off);
            printf("\n");
        }
        rc = 0;
        goto done;
    }
    if (chain) {
        /* Why a node's world comes out the way it does: the ancestor chain, each node's own matrix
         * (if any) and the composed world.  `--chain <substr>` prints every matching node. */
        for (j = 0; j < sc.nnode; j++) {
            const dw4_scene_node *n = &sc.node[j];
            float wm[16];
            uint32_t k;
            int q;

            if (!n->name || !strstr(n->name, chain_name))
                continue;
            printf("node %u %s %s\n", j, n->class_name, n->name);
            for (k = j; k != 0xFFFFFFFFu; k = sc.node[k].parent) {
                const dw4_scene_node *a = &sc.node[k];
                printf("   %4u d%-2u %-20s %-18s", k, a->depth, a->class_name, a->name ? a->name : "-");
                if (a->has_matrix) {
                    printf("  m =");
                    for (q = 0; q < 16; q++)
                        printf(" %.4f", (double)a->m[q]);
                } else
                    printf("  (inherits)");
                printf("\n");
                if (a->parent == k)
                    break;
            }
            dw4_scene_node_world(&sc, j, wm);
            printf("  world =");
            for (q = 0; q < 16; q++)
                printf(" %.4f", (double)wm[q]);
            printf("\n");
        }
        rc = 0;
        goto done;
    }
    if (world_tsv) {
        /* A `--scene` capture built from the pack's OWN scene graph: one row per geometry node (its
         * DCC name + composed world matrix) at the current time, so `render --scene` poses the pack
         * without a live capture.  This is how the front-end's animated scenes are drawn (finding
         * #610/#611). */
        for (j = 0; j < sc.nnode; j++) {
            const dw4_scene_node *n = &sc.node[j];
            float wm[16];
            int k;

            if (!n->class_name || strcmp(n->class_name, "igGeometry") != 0 || !n->name)
                continue;
            if (dw4_scene_node_world(&sc, j, wm) != 0)
                continue;
            printf("%s\t", n->name);
            for (k = 0; k < 16; k++)
                printf("%.6f%s", (double)wm[k], k == 15 ? "\n" : " ");
        }
        rc = 0;
        goto done;
    }
    if (tsv) {
        for (j = 0; j < sc.nmesh; j++)
            printf("%u\t%u\t%u\t%u\t%u\t%s\n", sc.mesh[j].attr_id, sc.mesh[j].prim_type,
                   sc.mesh[j].num_prims, sc.mesh[j].num_verts, sc.mesh[j].num_lengths,
                   sc.mesh[j].name ? sc.mesh[j].name : "");
        rc = 0;
        goto done;
    }
    for (j = 0; j < sc.nmesh; j++) {
        const dw4_scene_mesh *g = &sc.mesh[j];
        const char *why = NULL;
        uint32_t *tris = NULL, ntris = 0;
        char path[4096], base[256];
        FILE *fp;

        if (dw4_scene_tris(&sc, g, &tris, &ntris, &why) != 0) {
            fprintf(stderr, "  mesh %u (attr %u): SKIP (%s)\n", j, g->attr_id, why);
            continue;
        }
        free(tris);
        if (!out_dir) {
            if (list)
                printf("  %3u  %-24s attr %-7u %u verts, %u prims, %u tris  pos +0x%x uv +0x%x\n",
                       j, g->name ? g->name : "-", g->attr_id, g->num_verts, g->num_prims,
                       ntris, g->positions.off, g->uvs.off);
            continue;
        }
        dw4_mesh_obj_basename(g->name, g->vertex_array_id, base, sizeof(base));
        snprintf(path, sizeof(path), "%s/%s", out_dir, base);
        fp = fopen(path, "wb");
        if (!fp || dw4_scene_write_obj(&sc, g, fp) != 0) {
            fprintf(stderr, "scene: cannot write %s\n", path);
            if (fp)
                fclose(fp);
            rc = 1;
            continue;
        }
        fclose(fp);
    }
    if (list && !out_dir)
        printf("  %u mesh(es), named %u\n", sc.nmesh, (uint32_t)0);
    rc = 0;

done:
    dw4_scene_close(&sc);
    dw4_igfile_close(&f);
    if (have_mount)
        dw4_mount_close(&mnt);
    return rc;
}

/* --- the first renderer (P4.3): draw the loaded meshes into a PNG ---------------------------------
 *
 *   dw4asset render --afs A --entry N [--out sheet.png] [--w 640 --h 480] [--cols 6]
 *                   [--attr ID] [--yaw DEG] [--pitch DEG] [--wire]
 *
 * Every mesh of the pack is drawn into a grid cell with a camera fitted to it, shaded by a Lambert
 * term and tinted per mesh, so the geometry the loader produced is visible.  This is *not* the game's
 * own pipeline: the stage's object placement is a runtime assignment, so a stage's
 * layout cannot be drawn from the pack alone. */
/* One matched mesh in the merged scene: where its vertices and triangles sit in the merged
 * buffers, and a tint so neighbouring surfaces are told apart (the merge is one tint otherwise). */
typedef struct {
    uint32_t vb, nv, tb, nt;
    uint32_t uvb;            /* the draw's first UV in the merged uv array */
    float tint[3];
    char texname[64];        /* the scene row's sixth column: a live texture name, or "" */
    int ui;                  /* the row is the front-end's 2D layer (see cmd_render --ui-native) */
} dw4_draw;

/* The mesh's local bounding-box extent -- what separates a UI quad/sprite (a few hundred units at
 * most) from a world mesh in the same pack (thousands). */
static float mesh_local_extent(const float *pos, uint32_t n)
{
    float mn[3], mx[3];
    uint32_t i;
    int k;
    if (!n)
        return 0.0f;
    for (k = 0; k < 3; k++)
        mn[k] = mx[k] = pos[k];
    for (i = 1; i < n; i++)
        for (k = 0; k < 3; k++) {
            float v = pos[i * 3 + k];
            if (v < mn[k]) mn[k] = v;
            if (v > mx[k]) mx[k] = v;
        }
    {
        float e = 0.0f;
        for (k = 0; k < 3; k++) {
            float d = mx[k] - mn[k];
            if (d > e)
                e = d;
        }
        return e;
    }
}

/* The scene TSV's texture column names live textures (`texture_map.py`), which live in the stage's
 * texture packs.  A cache decodes each name once, trying every pack the caller listed; a name that
 * is nowhere is remembered as a miss so the packs are scanned once, not once per row. */
#define DW4_SCENE_TEXMAX 64
typedef struct {
    char name[64];
    uint8_t *rgba;
    dw4_tex t;
} dw4_scene_tex;
typedef struct {
    dw4_scene_tex tex[DW4_SCENE_TEXMAX];
    int n;
    const char *afs;
    uint32_t entries[16];
    int nentries;
    dw4_livetex *live;    /* --livedump: the same capture the --scene rows came from */
    const char *texdir;   /* --texdir: <name>.rgba files for inline pack textures */
} dw4_texcache;

/* An inline pack texture (the destructible objects' material is an igAttrSet in the stage pack,
 * not a texture pack: `scripts/pack_inline_tex.py` decodes it to `<name>.rgba`, a tiny
 * {u32 w}{u32 h}{rgba} file, so the scene path can sample it too).
 *
 * The file is the pack's own image order (row 0 = the first row the index data stores, which is
 * the GS's v=0), but the sampler indexes with `(1 - tv)` and so wants the
 * array bottom-up -- exactly what `dw4_texpack_rgba` produces for the texture packs, by reading
 * `grid + (h - 1 - y) * w`.  Flip the file here so both texture sources meet the sampler in one
 * convention; writing the .rgba pre-flipped instead is what made the props sample the mirrored
 * texel and the barrel's metal trim read pale. */
static void rgba_flip_rows(uint8_t *rgba, uint32_t w, uint32_t h)
{
    uint32_t y;
    for (y = 0; y < h / 2; y++) {
        uint8_t *a = rgba + (size_t)y * w * 4;
        uint8_t *b = rgba + (size_t)(h - 1 - y) * w * 4;
        uint32_t k;
        for (k = 0; k < w * 4; k++) {
            uint8_t t = a[k];
            a[k] = b[k];
            b[k] = t;
        }
    }
}

static dw4_tex *texcache_from_dir(dw4_texcache *tc, dw4_scene_tex *st, const char *name)
{
    char path[2048];
    FILE *fp;
    uint8_t hdr[8];
    uint32_t tw, th;
    uint8_t *rgba;
    snprintf(path, sizeof(path), "%s/%s.rgba", tc->texdir, name);
    fp = fopen(path, "rb");
    if (!fp)
        return NULL;
    if (fread(hdr, 1, 8, fp) != 8) {
        fclose(fp);
        return NULL;
    }
    tw = (uint32_t)hdr[0] | ((uint32_t)hdr[1] << 8) | ((uint32_t)hdr[2] << 16) | ((uint32_t)hdr[3] << 24);
    th = (uint32_t)hdr[4] | ((uint32_t)hdr[5] << 8) | ((uint32_t)hdr[6] << 16) | ((uint32_t)hdr[7] << 24);
    if (!tw || !th || tw > 4096 || th > 4096) {
        fclose(fp);
        return NULL;
    }
    rgba = (uint8_t *)malloc((size_t)tw * th * 4);
    if (rgba && fread(rgba, 1, (size_t)tw * th * 4, fp) == (size_t)tw * th * 4) {
        rgba_flip_rows(rgba, tw, th);
        st->rgba = rgba;
        st->t.rgba = rgba;
        st->t.w = (int)tw;
        st->t.h = (int)th;
    } else {
        free(rgba);
    }
    fclose(fp);
    return st->rgba ? &st->t : NULL;
}

static dw4_tex *texcache_get(dw4_texcache *tc, const char *name)
{
    int i, e;
    if (!name || !name[0])
        return NULL;
    if (!tc->afs && !tc->live && !tc->texdir)
        return NULL;
    for (i = 0; i < tc->n; i++)
        if (strcmp(tc->tex[i].name, name) == 0)
            return tc->tex[i].rgba ? &tc->tex[i].t : NULL;
    if (tc->n >= DW4_SCENE_TEXMAX)
        return NULL;
    dw4_scene_tex *st = &tc->tex[tc->n++];
    snprintf(st->name, sizeof(st->name), "%s", name);
    st->rgba = NULL;
    st->t.rgba = NULL;
    st->t.w = st->t.h = 0;
    /* A live dump first: it is the source that actually has a character/world material (finding
     * #525's residual), and a texture pack only holds the stage's environment images. */
    if (tc->live) {
        uint8_t *rgba = NULL;
        int tw = 0, th = 0;
        if (dw4_livetex_get(tc->live, name, &rgba, &tw, &th) == 0) {
            st->rgba = rgba;
            st->t.rgba = rgba;
            st->t.w = tw;
            st->t.h = th;
        }
    }
    for (e = 0; e < tc->nentries && !st->rgba && tc->afs; e++) {
        dw4_igfile tf;
        dw4_texpack tp;
        if (dw4_igfile_open_afs(&tf, tc->afs, tc->entries[e]) != 0)
            continue;
        if (dw4_texpack_open(&tp, dw4_igfile_data(&tf), dw4_igfile_size(&tf)) == 0) {
            const dw4_texpack_tex *t = dw4_texpack_find(&tp, name);
            if (t) {
                uint8_t *rgba = (uint8_t *)malloc((size_t)t->w * t->h * 4);
                if (rgba && dw4_texpack_rgba(&tp, t->image_id, t->clut_id, rgba) == 0) {
                    st->rgba = rgba;
                    st->t.rgba = rgba;
                    st->t.w = (int)t->w;
                    st->t.h = (int)t->h;
                } else {
                    free(rgba);
                }
            }
            dw4_texpack_close(&tp);
        }
        dw4_igfile_close(&tf);
    }
    if (!st->rgba && tc->texdir)
        texcache_from_dir(tc, st, name);
    return st->rgba ? &st->t : NULL;
}

static void texcache_free(dw4_texcache *tc)
{
    int i;
    for (i = 0; i < tc->n; i++)
        free(tc->tex[i].rgba);
    tc->n = 0;
    if (tc->live) {
        dw4_livetex_close(tc->live);
        tc->live = NULL;
    }
}

/* The per-mesh hash tint that used to live here is gone: the world materials
 * carry no `igMaterialAttr`/`igColorAttr`, and the GS's per-vertex colours (which the live rig
 * reproduces) are the only shade on the mesh, so a scene row defaults to white.  `--tint R,G,B`
 * still applies one constant colour to every row for an experiment. */

/* The light SPEC format (DW4_Port renderer P4.4) and its parser live in render.c
 * (`dw4_render_parse_light` / `dw4_render_load_lights`), so the software path, the GPU path and
 * the `dw4` host all consume exactly the same rig:
 *
 *   <dir|point|spot>,px,py,pz,dx,dy,dz,dr,dg,db,sr,sg,sb,range,shininess,falloff_deg,cutoff_deg
 *
 * `falloff`/`cutoff` are the inner/outer cone half-angles in degrees; an all-zero specular is
 * `_NOSPEC`.  A rig recovered later (e.g. by reading the populated `0x56AF40` list -- finding
 * #499) loads through `--lights FILE` with no code change. */

/* The mean face normal of one mesh, area-weighted -- the ground/wall split for the stage-material
 * fallback.  A mesh with no usable normal is treated as a wall. */
static void mesh_mean_normal(const uint8_t *pos, uint32_t nv, const uint32_t *tris, uint32_t nt,
                             float out[3])
{
    double n[3] = { 0, 0, 0 };
    out[0] = out[1] = out[2] = 0.0f;
    for (uint32_t k = 0; k < nt; k++) {
        float a[3], b[3], c[3], e1[3], e2[3];
        if (tris[3 * k] >= nv || tris[3 * k + 1] >= nv || tris[3 * k + 2] >= nv)
            continue;
        memcpy(a, pos + 12 * tris[3 * k], 12);
        memcpy(b, pos + 12 * tris[3 * k + 1], 12);
        memcpy(c, pos + 12 * tris[3 * k + 2], 12);
        for (int j = 0; j < 3; j++) {
            e1[j] = b[j] - a[j];
            e2[j] = c[j] - a[j];
        }
        n[0] += (double)e1[1] * e2[2] - (double)e1[2] * e2[1];
        n[1] += (double)e1[2] * e2[0] - (double)e1[0] * e2[2];
        n[2] += (double)e1[0] * e2[1] - (double)e1[1] * e2[0];
    }
    double L = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
    if (L > 1e-9) {
        out[0] = (float)(n[0] / L);
        out[1] = (float)(n[1] / L);
        out[2] = (float)(n[2] / L);
    }
}

/* --- the 2D UI overlay: replay the HUD a `.gs` dump recorded (`scripts/gs_ui.py`) ---------- *
 * One TSV row is one screen-space triangle: `TEX\tx y u v r g b a\t...` three times, where `TEX`
 * is a `<name>.rgba` in `texdir` or `-` for an untextured overlay.  The rows are drawn in file
 * order over the scene (the exporter emits them in the GS's draw order), with the blend
 * `dw4_render_ui_tri` implements.  Returns the triangle count, or -1 if the file cannot be read. */
/* One `ui.tsv` vertex: `nf` floats (`x y u v`, or `x y s t q` in the `#stq` form) then 4 ints. */


/* How many threads a replay uses: --ui-threads, else one per core (dw4_ui_draw_file's default). */
static int ui_threads = 0;

/* --ui-seq: the captured animated layer, cycled in time (dw4/uireplay.h).  One frame is the whole
 * front-end menu as the GS drew it -- logo, rows, cursor, copyright and the streaming additive light
 * trails; the layer cannot be a transform of one picture because the engine
 * regenerates its trails every frame, so the port cycles the engine's own captured frames. */
static dw4_uiseq *ui_seq = NULL;             /* opened on the first drawn frame */
static int ui_seq_draw(dw4_fb *fb, const char *dir, const char *texdir, double secs, double fps)
{
    if (!ui_seq)
        ui_seq = dw4_uiseq_open(dir, texdir, NULL, 1.0f, 1.0f);
    if (!ui_seq)
        return -1;
    return dw4_uiseq_draw_at(ui_seq, fb, secs, fps, ui_threads);
}


/* A mesh's per-vertex bone-index block: a pool block of exactly `num_verts` bytes whose bytes
 * are all small bone numbers.  Found by size, which is unique in the player's pack 861
 * (the pack's 354/2018/3580-byte blocks are the three shapes' bone streams).
 * A pack carries many same-sized blocks for other meshes, so the bone-range test is what
 * admits a block; a mesh with none keeps its bind pose. */
static const uint8_t *scene_bone_block(const dw4_scene *sp, uint32_t num_verts)
{
    uint32_t i, k;
    if (!sp || !sp->ent)
        return NULL;
    for (i = 0; i < sp->nent; i++) {
        const dw4_scene_ent *e = &sp->ent[i];
        const uint8_t *b;
        if (e->kind != 1 || e->size != num_verts)
            continue;
        b = (const uint8_t *)dw4_scene_host(sp, e->h);
        if (!b)
            continue;
        for (k = 0; k < num_verts; k++)
            if (b[k] > 0x40 || b[k] == 0)
                break;
        if (k == num_verts)
            return b;
    }
    return NULL;
}

static int cmd_render(int argc, char **argv)
{
    dw4_igfile f;
    dw4_scene sc;
    dw4_igfile f2;              /* --pack2: a second pack whose meshes a scene row may name */
    dw4_scene sc2;
    int have2 = 0;
    dw4_fb fb;
    dw4_mount mnt;
    const char *out = "render.png";
    const char *want_name = NULL;
    const char *texname = NULL;
    char deftx_ground[64] = "", deftx_wall[64] = "";  /* --default-tex G[,W]: the stage-material
                                                      * fallback for a scene row the material walk
                                                      * cannot name */
    const char *live_path = NULL;
    const char *texdir = NULL;   /* --texdir: <name>.rgba for inline pack textures */
    const char *ui_path = NULL;  /* --ui: scripts/gs_ui.py's ui.tsv, drawn over the scene */
    const char *ui_only = NULL;  /* --ui-only: draw one replay TSV alone (no scene) and exit */
    const char *ui_texdir = NULL;/* --uitex: where --ui's <name>.rgba files live */
    const char *ui_seq_dir = NULL; /* --ui-seq: a directory of per-frame animated-layer TSVs */
    double ui_seq_fps = 5.2;       /* --ui-seq-fps: how fast to step through them */
    int ui_native = 0;           /* --ui-native: draw the front-end's 2D rows in screen space */
    int osd_fps = -1;            /* --fps / --no-fps: -1 = on only when a window is presenting */
    const char *osd_text = NULL; /* --osd-text: a fixed string instead of the counter */
    float ui_scale = 1.0f;       /* --ui-scale: model units -> pixels */
    float ui_max_local = 400.0f; /* --ui-extent: only meshes this small are the 2D layer */
    int fe = 0;                  /* --fe: draw the pack's own scene as a front-end layer */
    const char *fe_scene = NULL; /* --fe-scene NAME: only this igSceneInfo's nodes (j_startback) */
    double fe_time = 0.0;        /* --time: the instant (ns) the animated nodes evaluate at */
    const char *rgba_path = NULL;/* --rgba: a raw RGBA texture for the layer */
    int rgba_w = 0, rgba_h = 0;  /* --rgba-w/--rgba-h */
    const char *scene_tsv = NULL;
    const char *pack2 = NULL;   /* --pack2 AFS:ENTRY */
    /* --pose-*: skin the character from the livedump (P4.1).  The select is the
     * skinned graph's igBlendMatrixSelect, the palette the igAnimationCombiner's matrix array
     * (+0x58), the node the beModelCtrlNode2 whose +0x20 matrix the character row already
     * carries -- the scene path applies it, so only the skinning itself is new here. */
    const char *pose_select_s = NULL, *pose_palette_s = NULL, *pose_node_s = NULL;
    uint32_t pose_select = 0, pose_palette = 0, pose_node = 0;
    int pose_count = 0;
    dw4_pose *pose = NULL;
    const char *out_dir = NULL;
    const char *camera_name = NULL;
    float viewm[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    float view_fov = 0.0f, view_aspect = 1.0f, spin = 0.0f;
    int frames = 1, have_view = 0, have_aspect = 0, have_camera = 0, have_clip = 0, fit = 0;
    const char *afs_path = NULL;
    uint32_t texentry = 625;
    uint8_t *tex_rgba = NULL;
    dw4_tex tex;
    int have_tex = 0;
    dw4_texcache tc;
    memset(&tc, 0, sizeof(tc));
    dw4_window *win = NULL;   /* --window: present the played frame(s) live (SDL2) */
    int want_window = 0;
    dw4_vk *vk = NULL;        /* --vulkan: present through a Vulkan swapchain instead */
    int use_vk = 0;
    int w = 640, h = 480, cols = 6, want_attr = -1, wire = 0, have = 0, have_mount = 0;
    int flat = 0;            /* --flat: ignore the vertex normals (the faceted baseline) */
    int normals_only = 0;    /* --normals-only: draw only meshes that ship a normal buffer */
    int limit = 48;
    float cam[3] = { 0, 0, 0 };
    float span = 0;                     /* 0 = fit each mesh's own bounds */
    float yaw = 0.6f, pitch = 0.35f;
    float amb[3] = { 0.3005f, 0.2444f, 0.2986f };   /* re-fitted live rig ambient */
    dw4_light lights[DW4_MAX_LIGHTS];
    dw4_fog fog;
    int nlights = 0, have_fog = 0, no_fog = 0;
    int white_tint = 0;      /* --white-tint: accepted, now the default (no hash palette) */
    int unlit = 0;           /* --unlit: skip the light term (igLightingStateAttr._enabled = 0) */
    float const_tint[3] = { 1.0f, 1.0f, 1.0f };   /* --tint R,G,B: one colour for every scene row */
    int have_const_tint = 0;
    uint32_t drawn = 0, skipped = 0, i;
    uint32_t withn = 0;      /* meshes that ship decoded vertex normals */
    int rc = 0;
    int use_gl = 0;          /* --gl: draw the --scene path on the GPU backend */
    dw4_gl *gl = NULL;

    memset(&f, 0, sizeof(f));
    memset(&mnt, 0, sizeof(mnt));
    for (int a = 0; a < argc; a++) {
        if (strcmp(argv[a], "--ambient") == 0 && a + 1 < argc) {
            const char *v = argv[++a];
            if (sscanf(v, "%f,%f,%f", &amb[0], &amb[1], &amb[2]) != 3)
                fprintf(stderr, "render: --ambient wants R,G,B\n");
        } else if (strcmp(argv[a], "--light") == 0 && a + 1 < argc) {
            if (nlights < DW4_MAX_LIGHTS && dw4_render_parse_light(argv[++a], &lights[nlights]) == 0)
                nlights++;
            else
                fprintf(stderr, "render: bad --light spec\n");
        } else if (strcmp(argv[a], "--lights") == 0 && a + 1 < argc) {
            int n = dw4_render_load_lights(argv[++a], lights, DW4_MAX_LIGHTS);
            if (n < 0) {
                fprintf(stderr, "render: cannot read the lights file\n");
                return 1;
            }
            nlights = n;
        } else if (strcmp(argv[a], "--white-tint") == 0)
            white_tint = 1;   /* the hash tint is gone; the flag is kept for old scripts */
        else if (strcmp(argv[a], "--unlit") == 0)
            unlit = 1;
        else if (strcmp(argv[a], "--gouraud") == 0)
            dw4_render_set_gouraud(1);
        else if (strcmp(argv[a], "--per-pixel") == 0)
            dw4_render_set_gouraud(0);
        else if (strcmp(argv[a], "--tint") == 0 && a + 1 < argc) {
            if (sscanf(argv[++a], "%f,%f,%f", &const_tint[0], &const_tint[1], &const_tint[2]) != 3)
                fprintf(stderr, "render: --tint wants R,G,B\n");
            else
                have_const_tint = 1;
        } else if (strcmp(argv[a], "--two-sided") == 0)
            dw4_render_set_two_sided(1);
        else if (strcmp(argv[a], "--one-sided") == 0)
            dw4_render_set_two_sided(0);
        else if (strcmp(argv[a], "--cull") == 0)
            dw4_render_set_cull(1);
        else if (strcmp(argv[a], "--cull-front") == 0)
            dw4_render_set_cull(2);
        else if (strcmp(argv[a], "--no-cull") == 0)
            dw4_render_set_cull(0);
        else if (strcmp(argv[a], "--uv-offset") == 0 && a + 1 < argc) {
            float u, v;
            if (sscanf(argv[++a], "%f,%f", &u, &v) != 2)
                fprintf(stderr, "render: --uv-offset wants U,V\n");
            else
                dw4_render_set_uv_offset(u, v);
        } else if (strcmp(argv[a], "--uv-scale") == 0 && a + 1 < argc)
            dw4_render_set_uv_scale((float)atof(argv[++a]));
        else if (strcmp(argv[a], "--nearest") == 0)
            dw4_render_set_tex_filter(0);
        else if (strcmp(argv[a], "--bilinear") == 0)
            dw4_render_set_tex_filter(1);
        else if (strcmp(argv[a], "--fog") == 0 && a + 1 < argc) {
            if (dw4_render_parse_fog(argv[++a], &fog) == 0)
                have_fog = 1;
            else
                fprintf(stderr, "render: bad --fog spec\n");
        } else if (strcmp(argv[a], "--no-fog") == 0)
            no_fog = 1;      /* force the GS fog stage off on a scene render (it is on by default) */
        else if (strcmp(argv[a], "--out") == 0 && a + 1 < argc)
            out = argv[++a];
        else if (strcmp(argv[a], "--w") == 0 && a + 1 < argc)
            w = atoi(argv[++a]);
        else if (strcmp(argv[a], "--h") == 0 && a + 1 < argc)
            h = atoi(argv[++a]);
        else if (strcmp(argv[a], "--cols") == 0 && a + 1 < argc)
            cols = atoi(argv[++a]);
        else if (strcmp(argv[a], "--attr") == 0 && a + 1 < argc)
            want_attr = atoi(argv[++a]);
        else if (strcmp(argv[a], "--name") == 0 && a + 1 < argc)
            want_name = argv[++a];
        else if (strcmp(argv[a], "--cam") == 0 && a + 2 < argc) {
            cam[0] = (float)atof(argv[a + 1]);
            cam[1] = (float)atof(argv[a + 2]);
            have_clip = 1;
            a += 2;
        } else if (strcmp(argv[a], "--span") == 0 && a + 1 < argc)
            span = (float)atof(argv[++a]);
        else if (strcmp(argv[a], "--fit") == 0)
            fit = 1;
        else if (strcmp(argv[a], "--camera") == 0) {
            have_camera = 1;
            if (a + 1 < argc && argv[a + 1][0] != '-')
                camera_name = argv[++a];
        }
        else if (strcmp(argv[a], "--scene") == 0 && a + 1 < argc)
            scene_tsv = argv[++a];
        else if (strcmp(argv[a], "--frames") == 0 && a + 1 < argc)
            frames = atoi(argv[++a]);
        else if (strcmp(argv[a], "--spin") == 0 && a + 1 < argc)
            spin = (float)atof(argv[++a]);
        else if (strcmp(argv[a], "--fov") == 0 && a + 1 < argc)
            view_fov = (float)atof(argv[++a]);
        else if (strcmp(argv[a], "--aspect") == 0 && a + 1 < argc) {
            view_aspect = (float)atof(argv[++a]);
            have_aspect = 1;
        }
        else if (strcmp(argv[a], "--out-dir") == 0 && a + 1 < argc)
            out_dir = argv[++a];
        else if (strcmp(argv[a], "--pack2") == 0 && a + 1 < argc)
            pack2 = argv[++a];
        else if (strcmp(argv[a], "--pose-select") == 0 && a + 1 < argc)
            pose_select_s = argv[++a];
        else if (strcmp(argv[a], "--pose-palette") == 0 && a + 1 < argc)
            pose_palette_s = argv[++a];
        else if (strcmp(argv[a], "--pose-node") == 0 && a + 1 < argc)
            pose_node_s = argv[++a];
        else if (strcmp(argv[a], "--pose-count") == 0 && a + 1 < argc)
            pose_count = atoi(argv[++a]);
        else if (strcmp(argv[a], "--view") == 0 && a + 1 < argc) {
            int k;
            char *v = argv[++a];
            for (k = 0; k < 16; k++)
                viewm[k] = (float)strtod(v, &v);
            have_view = 1;
        }
        else if (strcmp(argv[a], "--texdir") == 0 && a + 1 < argc)
            texdir = argv[++a];
        else if (strcmp(argv[a], "--ui") == 0 && a + 1 < argc)
            ui_path = argv[++a];
        else if (strcmp(argv[a], "--ui-only") == 0 && a + 1 < argc)
            ui_only = argv[++a];
        else if (strcmp(argv[a], "--ui-native") == 0) {
            ui_native = 1;
            if (a + 1 < argc && argv[a + 1][0] != '-')
                ui_scale = (float)atof(argv[++a]);
        } else if (strcmp(argv[a], "--ui-extent") == 0 && a + 1 < argc) {
            ui_max_local = (float)atof(argv[++a]);
        } else if (strcmp(argv[a], "--ui-scale") == 0 && a + 1 < argc) {
            ui_scale = (float)atof(argv[++a]);
        } else if (strcmp(argv[a], "--uitex") == 0 && a + 1 < argc)
            ui_texdir = argv[++a];
        else if (strcmp(argv[a], "--fe") == 0)
            fe = 1;                       /* draw the pack's own scene as the front-end layer */
        else if (strcmp(argv[a], "--fe-scene") == 0 && a + 1 < argc)
            fe_scene = argv[++a];         /* restrict the layer to one named scene graph */
        else if (strcmp(argv[a], "--time") == 0 && a + 1 < argc)
            fe_time = strtod(argv[++a], NULL);
        else if (strcmp(argv[a], "--rgba") == 0 && a + 1 < argc)
            rgba_path = argv[++a];
        else if (strcmp(argv[a], "--rgba-w") == 0 && a + 1 < argc)
            rgba_w = atoi(argv[++a]);
        else if (strcmp(argv[a], "--rgba-h") == 0 && a + 1 < argc)
            rgba_h = atoi(argv[++a]);
        else if (strcmp(argv[a], "--ui-seq") == 0 && a + 1 < argc)
            ui_seq_dir = argv[++a];          /* the cycling animated layer (see ui_seq_frame) */
        else if (strcmp(argv[a], "--ui-seq-fps") == 0 && a + 1 < argc)
            ui_seq_fps = atof(argv[++a]);
        else if (strcmp(argv[a], "--fps") == 0)
            osd_fps = 1;
        else if (strcmp(argv[a], "--no-fps") == 0)
            osd_fps = 0;
        else if (strcmp(argv[a], "--osd-text") == 0 && a + 1 < argc) {
            osd_text = argv[++a];       /* a fixed readout, so a check can pin the drawing */
            osd_fps = 1;
        }
        else if (strcmp(argv[a], "--texture") == 0 && a + 1 < argc)
            texname = argv[++a];
        else if (strcmp(argv[a], "--texentry") == 0 && a + 1 < argc) {
            /* one texture-pack entry, or a comma-separated list the scene's texture column is
             * resolved against (a mesh's texture can live in any of the stage's several packs) */
            char *q = argv[++a];
            tc.nentries = 0;
            while (*q && tc.nentries < 16) {
                char *end;
                unsigned long v = strtoul(q, &end, 0);
                if (end == q)
                    break;
                tc.entries[tc.nentries++] = (uint32_t)v;
                q = end;
                if (*q == ',')
                    q++;
                else
                    break;
            }
            if (tc.nentries)
                texentry = tc.entries[0];
        }
        else if (strcmp(argv[a], "--default-tex") == 0 && a + 1 < argc) {
            /* The stage-material fallback: a scene row with no recovered texture gets G when the
             * mesh's mean normal is up-facing, else W (or G when W is absent).  The names come from
             * the material walk (camera_match --stage-material); this is a join fallback, not a
             * recovered binding. */
            const char *v = argv[++a];
            const char *comma = strchr(v, ',');
            size_t n = comma ? (size_t)(comma - v) : strlen(v);
            if (n >= sizeof(deftx_ground))
                n = sizeof(deftx_ground) - 1;
            memcpy(deftx_ground, v, n);
            deftx_ground[n] = 0;
            if (comma && comma[1])
                snprintf(deftx_wall, sizeof(deftx_wall), "%s", comma + 1);
        }
        else if (strcmp(argv[a], "--livedump") == 0 && a + 1 < argc) {
            live_path = argv[++a];
        }
        else if (strcmp(argv[a], "--gl") == 0)
            use_gl = 1;
        else if (strcmp(argv[a], "--window") == 0)
            want_window = 1;
        else if (strcmp(argv[a], "--wire") == 0)
            wire = 1;
        else if (strcmp(argv[a], "--flat") == 0)
            flat = 1;
        else if (strcmp(argv[a], "--ui-threads") == 0 && a + 1 < argc)
            ui_threads = atoi(argv[++a]);        /* 1 = the serial replay, for the identity check */
        else if (strcmp(argv[a], "--vk") == 0 || strcmp(argv[a], "--vulkan") == 0) {
            use_vk = 1;
            want_window = 1;         /* presenting through Vulkan means presenting */
        } else if (strcmp(argv[a], "--vk-device") == 0)
            use_vk = 1;              /* no --window: initialise the device only, present nothing */
        else if (strcmp(argv[a], "--normals-only") == 0)
            normals_only = 1;
        else if (strcmp(argv[a], "--limit") == 0 && a + 1 < argc)
            limit = atoi(argv[++a]);
        else if (strcmp(argv[a], "--yaw") == 0 && a + 1 < argc)
            yaw = (float)atof(argv[++a]) * 3.14159265f / 180.0f;
        else if (strcmp(argv[a], "--pitch") == 0 && a + 1 < argc)
            pitch = (float)atof(argv[++a]) * 3.14159265f / 180.0f;
        else if (strcmp(argv[a], "--stage") == 0 && a + 3 < argc) {
            const char *roms = argv[++a], *stage = argv[++a];
            uint32_t idx = 0;
            if (a + 1 < argc && strcmp(argv[a + 1], "--ref") == 0 && a + 2 < argc) {
                idx = (uint32_t)strtoul(argv[a + 2], NULL, 0);
                a += 2;
            }
            if (dw4_mount_open(&mnt, roms) != 0 || dw4_igfile_open_stage_ref(&f, &mnt, stage, idx) != 0)
                return 1;
            have = have_mount = 1;
        } else if (strcmp(argv[a], "--afs") == 0 && a + 1 < argc) {
            const char *path = argv[++a];
            afs_path = path;
            if (a + 1 < argc && strcmp(argv[a + 1], "--entry") == 0 && a + 2 < argc) {
                uint32_t e = (uint32_t)strtoul(argv[a + 2], NULL, 0);
                a += 2;
                if (dw4_igfile_open_afs(&f, path, e) != 0)
                    return 1;
                have = 1;
            }
        } else if (argv[a][0] != '-' && !have) {
            if (dw4_igfile_open_path(&f, argv[a]) != 0)
                return 1;
            have = 1;
        }
    }
    if (!have) {
        fprintf(stderr, "usage: dw4asset render <file>|--afs A --entry N|--stage R <stage.igb>"
                        " [--ref N] [--out f.png] [--w N --h N] [--cols N] [--attr ID] [--name S]"
                        " [--texture NAME --texentry N] [--default-tex G[,W]] [--texdir D] [--pack2 AFS:ENTRY]"
                        " [--livedump RAM.bin]"
                        " [--scene TSV] [--gl] [--yaw DEG] [--pitch DEG] [--wire]"
                        " [--fit|--camera [NAME]|--view 'm0 .. m15'] [--fov RAD] [--aspect A]"
                        " [--cam X Y Z --span N]"
                        " [--ambient R,G,B] [--light SPEC] [--lights FILE]"
                        " [--fog SPEC | --no-fog] (the game's own stage fog is the scene default)\n");
        return 2;
    }
    /* The lighting rig (P4.4): the shading model is the game's, the values are supplied here
     * because the disc and the savestates do not carry them. */
    dw4_render_set_ambient(amb[0], amb[1], amb[2]);
    if (unlit)
        dw4_render_set_unlit(1);
    (void)white_tint;
    if (nlights)
        dw4_render_set_lights(lights, nlights);
    if (have_fog)
        dw4_render_set_fog(&fog);
    else if (scene_tsv && !no_fog) {
        /* The game's own stage fog (the GS fog stage) is the default for a
         * scene render, because the reference framebuffer carries it and every region improves
         * (whole 14.70 -> 10.96 at --blur 1.2).  `--fog` overrides, `--no-fog` drops it. */
        dw4_fog gf;
        if (dw4_render_game_fog(&gf) == 0)
            dw4_render_set_fog(&gf);
    }
    /* The GL path consumes the same rig; with no caller rig it uses render.c's built-in game rig,
     * so both backends shade the same frame. */
    dw4_light builtin_rig[DW4_MAX_LIGHTS];
    const dw4_light *rig = lights;
    int nrig = nlights;
    if (nlights == 0) {
        nrig = dw4_render_builtin_rig(builtin_rig, DW4_MAX_LIGHTS);
        rig = builtin_rig;
    }
    /* An optional texture, from a texture pack's own name: this proves the mesh's UV pipeline
     * against real game data.  The model -> texture *binding* is a different question -- it lives on
     * igTextureBindAttr -> igTextureAttr -> igImage, and nothing in the pack links a mesh to it
     * -- so the caller names the texture for now. */
    memset(&tex, 0, sizeof(tex));
    if (!tc.nentries) {
        tc.entries[0] = texentry;
        tc.nentries = 1;
    }
    tc.afs = afs_path;
    tc.texdir = texdir;
    if (live_path) {
        tc.live = dw4_livetex_open(live_path);
        if (!tc.live)
            fprintf(stderr, "render: --livedump %s is not a 31/32 MB EE RAM image\n", live_path);
        else
            printf("  livedump %s: %d named texture(s)\n", live_path,
                   dw4_livetex_count(tc.live));
    }
    if (pose_select_s || pose_palette_s || pose_node_s) {
        if (!live_path)
            fprintf(stderr, "render: --pose-* needs --livedump (the skinning state lives there)\n");
        else if (!pose_select_s || !pose_palette_s || !pose_node_s || !pose_count)
            fprintf(stderr, "render: --pose-* needs --pose-select, --pose-palette, --pose-node "
                            "and --pose-count\n");
        else {
            pose = dw4_pose_open(live_path);
            if (pose) {
                pose_select = (uint32_t)strtoul(pose_select_s, NULL, 0);
                pose_palette = (uint32_t)strtoul(pose_palette_s, NULL, 0);
                pose_node = (uint32_t)strtoul(pose_node_s, NULL, 0);
                if (dw4_pose_config(pose, pose_select, pose_palette, pose_count, pose_node) != 0)
                    fprintf(stderr, "render: --pose-* chain did not resolve\n");
                else
                    printf("  pose: select %08x, palette %08x (%d matrices), node %08x\n",
                           pose_select, pose_palette, pose_count, pose_node);
            } else
                fprintf(stderr, "render: --pose-* cannot read %s\n", live_path);
        }
    }
    if (texname && (afs_path || tc.live)) {
        if (tc.live) {
            uint8_t *rgba = NULL;
            int tw = 0, th = 0;
            if (dw4_livetex_get(tc.live, texname, &rgba, &tw, &th) == 0) {
                tex_rgba = rgba;
                tex.rgba = rgba;
                tex.w = tw;
                tex.h = th;
                have_tex = 1;
                printf("texture %s: %dx%d from the livedump\n", texname, tw, th);
            } else {
                fprintf(stderr, "render: no texture %s in the livedump\n", texname);
            }
        }
        if (!have_tex && afs_path) {
        dw4_igfile tf;
        dw4_texpack tp;
        if (dw4_igfile_open_afs(&tf, afs_path, texentry) == 0) {
            if (dw4_texpack_open(&tp, dw4_igfile_data(&tf), dw4_igfile_size(&tf)) == 0) {
                const dw4_texpack_tex *t = dw4_texpack_find(&tp, texname);
                if (t) {
                    tex_rgba = (uint8_t *)malloc((size_t)t->w * t->h * 4);
                    if (tex_rgba && dw4_texpack_rgba(&tp, t->image_id, t->clut_id, tex_rgba) == 0) {
                        tex.rgba = tex_rgba;
                        tex.w = (int)t->w;
                        tex.h = (int)t->h;
                        have_tex = 1;
                        printf("texture %s: %ux%u from %s entry %u\n", t->name, t->w, t->h,
                               afs_path, texentry);
                    }
                } else {
                    fprintf(stderr, "render: no texture %s in entry %u\n", texname, texentry);
                }
                dw4_texpack_close(&tp);
            }
            dw4_igfile_close(&tf);
        }
        }
    }
    if (dw4_scene_load(&sc, dw4_igfile_data(&f), dw4_igfile_size(&f)) != 0) {
        fprintf(stderr, "render: %s is not a loadable pack\n", f.path);
        return 1;
    }
    /* A second pack the scene rows may name (the player's `P_susanoo_Skin0Shape*` live in
     * NDMW.AFS:861, not in the stage's pack).  A row resolves in the first pack that
     * has its id, so the stage's 566 meshes and the player's 3 can share one TSV. */
    if (pack2) {
        char *colon = strrchr(pack2, ':');
        if (colon) {
            *colon = 0;
            if (dw4_igfile_open_afs(&f2, pack2, (uint32_t)strtoul(colon + 1, NULL, 0)) == 0 &&
                dw4_scene_load(&sc2, dw4_igfile_data(&f2), dw4_igfile_size(&f2)) == 0)
                have2 = 1;
            else
                fprintf(stderr, "render: --pack2 %s:%s could not be loaded\n", pack2, colon + 1);
            *colon = ':';
        }
    }
    /* Framing.  `--camera` uses the pack's own camera -- the game's framing --
     * with the measured 39.60 deg fov and the PS2 640x448 projection; `--fit` instead fits the
     * drawn geometry's own bounds (the default when neither is given); `--view` overrides both. */
    if (have_camera) {
        float cw[16], cv[16];
        int node = dw4_scene_camera(&sc, camera_name, cw, cv);
        if (node < 0) {
            fprintf(stderr, "render: no igCamera %s in %s\n",
                    camera_name ? camera_name : "(stage)", f.name[0] ? f.name : f.path);
            dw4_scene_close(&sc);
            dw4_igfile_close(&f);
            if (have_mount)
                dw4_mount_close(&mnt);
            return 1;
        }
        if (!have_view) {
            memcpy(viewm, cv, sizeof(viewm));
            have_view = 1;
            if (view_fov <= 0.0f)
                view_fov = DW4_SCENE_CAMERA_FOV;
            if (!have_aspect)
                view_aspect = dw4_scene_camera_aspect(w, h);
        }
        printf("  camera %-20s node %d at (%8.3f %8.3f %8.3f), fov %.4f rad, aspect %.4f\n",
               sc.node[node].name ? sc.node[node].name : "-", node,
               (double)cw[12], (double)cw[13], (double)cw[14], (double)view_fov,
               (double)view_aspect);
    }
    if (fit)
        have_view = 0;                     /* explicit: fit the geometry, ignore any camera */
    if (have_view && view_fov > 0.0f) {
        /* apply the view for the single-mesh paths too; the scene run below rebuilds it per frame
         * (with the spin), and both negate the third row because the projection divides by +z */
        float v2[16];
        int k;
        memcpy(v2, viewm, sizeof(v2));
        for (k = 0; k < 4; k++)
            v2[8 + k] = -v2[8 + k];
        dw4_render_set_view(v2, view_fov,
                            have_aspect ? view_aspect : dw4_scene_camera_aspect(w, h));
    }
    if (dw4_fb_init(&fb, w, h) != 0) {
        dw4_scene_close(&sc);
        dw4_igfile_close(&f);
        if (have_mount)
            dw4_mount_close(&mnt);
        return 1;
    }
    if (ui_only) {
        /* Draw one replay TSV alone (no scene), which is how the captured front-end layers are
         * inspected: `dw4asset render <pack> --ui-only ui000.tsv --uitex DIR --out f.png`. */
        int t;
        dw4_fb_clear(&fb, 0, 0, 0);
        t = dw4_ui_draw_file(&fb, ui_only, ui_texdir ? ui_texdir : ".", ui_threads, NULL, 1.0f, 1.0f);
        printf("ui-only: %d triangle(s) from %s (textures in %s)\n", t, ui_only,
               ui_texdir ? ui_texdir : ".");
        drawn = (uint32_t)(t > 0 ? t : 0);
        rc = 0;
        goto fe_out;
    }
    if (fe) {
        /* The front-end's own layer, generated by the port instead of replayed from a capture
         *: the pack's scene graph is posed at `--time`, each geometry node's mesh is
         * projected into SCREEN space (the origin at the framebuffer centre, +x right, +y up, the
         * same 2D setup the UI rows use) and composited additively through the GS UI primitive. */
        const uint8_t rgba[3][4] = { { 63, 63, 70, 127 }, { 63, 63, 70, 127 },
                                     { 63, 63, 70, 127 } };
        dw4_tex ftex;
        int have_ftex = 0;
        uint32_t j, k, q2, nnodes = 0, ntris_drawn = 0;
        uint32_t fe_gi = 0xFFFFFFFFu;      /* the graph index `--fe-scene` selected */

        memset(&ftex, 0, sizeof(ftex));
        if (rgba_path && rgba_w > 0 && rgba_h > 0) {
            FILE *rf = fopen(rgba_path, "rb");
            size_t need = (size_t)rgba_w * rgba_h * 4;
            uint8_t *buf = (uint8_t *)malloc(need);
            if (rf && buf && fread(buf, 1, need, rf) == need) {
                ftex.rgba = buf;
                ftex.w = rgba_w;
                ftex.h = rgba_h;
                have_ftex = 1;
                printf("fe-layer texture %s: %dx%d\n", rgba_path, rgba_w, rgba_h);
            } else {
                free(buf);
                fprintf(stderr, "render: --rgba %s could not be read as %dx%d RGBA\n", rgba_path,
                        rgba_w, rgba_h);
            }
            if (rf)
                fclose(rf);
        }
        dw4_scene_set_time(&sc, fe_time);
        if (fe_scene) {
            for (j = 0; j < sc.ngraph; j++)
                if (sc.graph[j].name && strcmp(sc.graph[j].name, fe_scene) == 0) {
                    fe_gi = j;
                    break;
                }
            if (fe_gi == 0xFFFFFFFFu)
                fprintf(stderr, "render: --fe-scene %s: no such scene graph\n", fe_scene);
            else
                printf("fe-layer scene '%s': %u node(s)\n", fe_scene, sc.graph[fe_gi].nnodes);
        }
        for (j = 0; j < sc.nnode; j++) {
            const dw4_scene_node *n = &sc.node[j];
            const dw4_scene_mesh *m = NULL;
            const float *pos, *uv;
            uint32_t *tris = NULL, nt = 0;
            const char *why = NULL;
            float wm[16];

            if (fe_scene && n->scene != fe_gi)
                continue;
            if (!n->class_name || strcmp(n->class_name, "igGeometry") != 0 || !n->name)
                continue;
            for (k = 0; k < sc.nmesh; k++)
                if (sc.mesh[k].name && strcmp(sc.mesh[k].name, n->name) == 0) {
                    m = &sc.mesh[k];
                    break;
                }
            if (!m || dw4_scene_node_world(&sc, j, wm) != 0)
                continue;
            pos = (const float *)dw4_scene_host(&sc, m->positions);
            uv = m->uvs.off ? (const float *)dw4_scene_host(&sc, m->uvs) : NULL;
            if (!pos || dw4_scene_tris(&sc, m, &tris, &nt, &why) != 0)
                continue;
            for (q2 = 0; q2 < nt; q2++) {
                float v[3][4];
                int e;
                for (e = 0; e < 3; e++) {
                    uint32_t vi = tris[3 * q2 + e];
                    float x, y, z;
                    if (vi >= m->num_verts)
                        break;
                    x = pos[3 * vi];
                    y = pos[3 * vi + 1];
                    z = pos[3 * vi + 2];
                    v[e][0] = w * 0.5f + ui_scale * (x * wm[0] + y * wm[4] + z * wm[8] + wm[12]);
                    v[e][1] = h * 0.5f - ui_scale * (x * wm[1] + y * wm[5] + z * wm[9] + wm[13]);
                    v[e][2] = uv ? uv[2 * vi] : 0.0f;
                    v[e][3] = uv ? uv[2 * vi + 1] : 0.0f;
                }
                if (e != 3)
                    continue;
                dw4_render_ui_tri(&fb, v[0], v[1], v[2], rgba, have_ftex ? &ftex : NULL, 1);
                ntris_drawn++;
            }
            free(tris);
            nnodes++;
        }
        printf("fe-layer: %u node(s), %u triangle(s) drawn in screen space (scale %.3f, t=%.0f ns)\n",
               nnodes, ntris_drawn, (double)ui_scale, fe_time);
        free((void *)ftex.rgba);
        drawn = nnodes;
        rc = 0;
        goto fe_out;
    }
    if (use_gl) {
        gl = dw4_gl_open(w, h);
        if (!gl) {
            fprintf(stderr, "render: --gl requested but no GL context (%s)\n",
                    dw4_gl_built() ? "EGL/GLES open failed" : "EGL/GLES not compiled in");
            dw4_fb_free(&fb);
            dw4_scene_close(&sc);
            dw4_igfile_close(&f);
            if (have_mount)
                dw4_mount_close(&mnt);
            return 1;
        }
        printf("  gl: %s, %dx%d offscreen FBO\n", dw4_gl_info(gl), w, h);
        if (!scene_tsv && !want_name && want_attr < 0)
            fprintf(stderr, "render: --gl applies to the --scene and --name/--attr paths;"
                            " the mesh sheet stays software\n");
    }
    dw4_fb_clear(&fb, 24, 28, 36);
    {
        /* a sheet shows the first `limit` meshes in a grid, so the cells are as large as the
         * frame allows (drawing all 549 into one image would leave them 8 pixels tall) */
        uint32_t rows = (uint32_t)((limit + cols - 1) / cols);
        uint32_t cell_h = rows ? (uint32_t)h / rows : (uint32_t)h;
        uint32_t cell_w = (uint32_t)w / (uint32_t)cols;
        for (i = 0; i < sc.nmesh; i++) {
            const dw4_scene_mesh *g = &sc.mesh[i];
            const uint8_t *pos;
            uint32_t *tris = NULL, ntris = 0;
            const char *why = NULL;
            float tint[3];
            uint32_t cx, cy;
            int use = 1;

            if (want_attr >= 0 && (int)g->attr_id != want_attr)
                use = 0;
            if (want_name && (!g->name || strcmp(g->name, want_name) != 0))
                use = 0;
            if (normals_only && !g->normals.off)
                use = 0;
            if (!use)
                continue;
            pos = (const uint8_t *)dw4_scene_host(&sc, g->positions);
            if (!pos || dw4_scene_tris(&sc, g, &tris, &ntris, &why) != 0) {
                skipped++;
                continue;
            }
            if (g->normals.off)
                withn++;
            tint[0] = tint[1] = tint[2] = 1.0f;
            if (have_const_tint) {
                tint[0] = const_tint[0]; tint[1] = const_tint[1]; tint[2] = const_tint[2];
            }
            if (want_attr >= 0 || want_name) {
                /* one model, full frame; the mesh's own vertex normals smooth it */
                const uint8_t *nrm = flat ? NULL
                                          : (const uint8_t *)dw4_scene_host(&sc, g->normals);
                const uint8_t *uvp = (const uint8_t *)dw4_scene_host(&sc, g->uvs);
                if (gl) {
                    float gv[16];
                    const float *gvv;
                    float gfov, gaspect;
                    if (have_view && view_fov > 0.0f) {
                        int kk;
                        memcpy(gv, viewm, sizeof(gv));
                        for (kk = 0; kk < 4; kk++)
                            gv[8 + kk] = -gv[8 + kk];
                        gfov = view_fov;
                        gaspect = have_aspect ? view_aspect : dw4_scene_camera_aspect(w, h);
                    } else {
                        dw4_render_fit_view(pos, g->num_verts, yaw, pitch, gv, &gfov, &gaspect);
                    }
                    gvv = gv;
                    dw4_gl_render(gl, &fb, (const float *)pos, (const float *)nrm,
                                  (const float *)uvp, tris, g->num_verts, ntris, gvv, gfov,
                                  gaspect, amb, rig, nrig, tint, have_tex ? &tex : NULL);
                } else if (wire)
                    dw4_render_wire(&fb, pos, g->num_verts, tris, ntris, yaw, pitch, w, 255, 255, 0);
                else
                    dw4_render_mesh_n(&fb, pos, nrm, uvp, g->num_verts, tris, ntris, yaw, pitch,
                                      tint, have_tex ? &tex : NULL);
                drawn++;
            } else {
                /* each cell is drawn into its own buffer and copied in, so the camera maths needs
                 * no origin handling */
                cx = (drawn % cols) * cell_w;
                cy = (drawn / cols) * cell_h;
                {
                    dw4_fb sub;
                    uint32_t y;
                    sub.w = (int)cell_w;
                    sub.h = (int)cell_h;
                    /* a temporary buffer per cell keeps the transform maths simple */
                    if (dw4_fb_init(&sub, (int)cell_w, (int)cell_h) != 0)
                        break;
                    dw4_fb_clear(&sub, 24, 28, 36);
                    if (wire)
                        dw4_render_wire(&sub, pos, g->num_verts, tris, ntris, yaw, pitch, w, 255,
                                        255, 0);
                    else
                        dw4_render_mesh_n(&sub, pos,
                                          flat ? NULL : (const uint8_t *)dw4_scene_host(&sc, g->normals),
                                          (const uint8_t *)dw4_scene_host(&sc, g->uvs),
                                          g->num_verts, tris, ntris, yaw, pitch, tint, NULL);
                    for (y = 0; y < cell_h && cy + y < (uint32_t)h; y++) {
                        uint32_t n = cell_w;
                        if (cx + n > (uint32_t)w)
                            n = (uint32_t)w - cx;
                        memcpy(fb.rgba + 4 * ((size_t)(cy + y) * w + cx),
                               sub.rgba + 4 * ((size_t)y * cell_w), 4 * n);
                        memcpy(fb.z + (size_t)(cy + y) * w + cx, sub.z + (size_t)y * cell_w,
                               n * sizeof(float));
                    }
                    dw4_fb_free(&sub);
                }
                drawn++;
            }
            free(tris);
        }
    }
    /* A captured scene: one row per placed node -- the model's DCC name, its world matrix, and the
     * geometry-attribute addresses a live capture found.  The *name* is the link to
     * the pack: every mesh with that name is transformed by the matrix and merged into one buffer,
     * so the camera fits the whole stage and the geometry is drawn where the game puts it. */
    if (scene_tsv) {
        FILE *fp = fopen(scene_tsv, "r");
        if (!fp) {
            fprintf(stderr, "render: cannot read %s\n", scene_tsv);
            rc = 1;
        } else {
            char line[8192];
            float *xyz = NULL, *uv = NULL, *nrm = NULL;
            dw4_draw *draws = NULL;
            uint32_t ndraw = 0, ncap = 0;
            float *sxyz = NULL, *suv = NULL, *snrm = NULL, *stint = NULL;
            uint32_t *stris = NULL, scapv = 0, scapt = 0;
            uint32_t *tris = NULL;
            uint32_t nv = 0, nt = 0, capv = 0, capt = 0, placed = 0, missing = 0;
            /* --pose-* scratch: the posed vertices/normals of one mesh at a time */
            float *pxyz = NULL, *pnrm = NULL;
            uint32_t pcap = 0;
            uint32_t posed_rows = 0;
            while (fgets(line, sizeof(line), fp)) {
                char name[128], *fld[6];
                float m[16];
                int nf = 0, got = 0, nids = 0, k, si;
                int32_t ids[16];
                char tex0[64] = "";
                char *p = line;
                while (nf < 6 && p && *p && *p != '\n') {
                    fld[nf++] = p;
                    p = strchr(p, '\t');
                    if (p)
                        *p++ = 0;
                }
                if (nf < 2)
                    continue;
                snprintf(name, sizeof(name), "%s", fld[0]);
                if (sscanf(fld[1], "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
                           &m[0], &m[1], &m[2], &m[3], &m[4], &m[5], &m[6], &m[7], &m[8], &m[9],
                           &m[10], &m[11], &m[12], &m[13], &m[14], &m[15]) != 16)
                    continue;
                /* A fifth column (capture_scene --pack) holds the pack geometry-attribute ids,
                 * the unique link needed: names repeat and the large environment
                 * meshes have none, so a name join over-draws.  Without the column, fall back
                 * to the name. */
                if (nf >= 5 && fld[4][0]) {
                    char *q = fld[4];
                    while (*q && nids < 16) {
                        char *end;
                        long v = strtol(q, &end, 0);
                        if (end == q)
                            break;
                        ids[nids++] = (int32_t)v;
                        q = end;
                        if (*q == ',')
                            q++;
                        else
                            break;
                    }
                }
                /* A sixth column (capture_scene/camera_match --textures) names the live texture of
                 * this row; only the first name is used (a row is one material). */
                if (nf >= 6 && fld[5][0]) {
                    /* the first name only (a row is one material); stop before the newline */
                    size_t n = strcspn(fld[5], ",\r\n\t");
                    if (n >= sizeof(tex0))
                        n = sizeof(tex0) - 1;
                    memcpy(tex0, fld[5], n);
                    tex0[n] = 0;
                }
                for (si = 0; si < (have2 ? 2 : 1) && !got; si++) {
                  dw4_scene *sp = si ? &sc2 : &sc;
                  for (i = 0; i < sp->nmesh; i++) {
                    const dw4_scene_mesh *g = &sp->mesh[i];
                    const uint8_t *pos, *guv, *gnrm;
                    uint32_t *gt = NULL, gnt = 0;
                    const char *why = NULL;
                    if (nids) {
                        int hit = 0;
                        for (k = 0; k < nids; k++)
                            if ((int32_t)g->attr_id == ids[k]) {
                                hit = 1;
                                break;
                            }
                        if (!hit)
                            continue;
                    } else if (!g->name || strcmp(g->name, name) != 0) {
                        continue;
                    }
                    pos = (const uint8_t *)dw4_scene_host(sp, g->positions);
                    guv = (const uint8_t *)dw4_scene_host(sp, g->uvs);
                    /* `--flat` (the faceted baseline) drops the vertex normals, so the renderer
                     * shades every triangle with its face normal -- exactly the old frame */
                    gnrm = (!flat && g->normals.off)
                               ? (const uint8_t *)dw4_scene_host(sp, g->normals)
                               : NULL;
                    /* --pose-*: skin this mesh when the pack carries its per-vertex bone block
                     * (a pool block of exactly num_verts bytes, all small bone numbers -- the
                     * player's are 5483/5595/5566 in pack 861).  The skinned
                     * vertices stay in model space; the row matrix below places them, which is
                     * the node matrix the chain was verified against. */
                    if (pose) {
                        const uint8_t *bones = scene_bone_block(sp, g->num_verts);
                        if (bones) {
                            if (pcap < g->num_verts) {
                                pcap = g->num_verts * 2 + 64;
                                pxyz = (float *)realloc(pxyz, (size_t)pcap * 3 * sizeof(float));
                                pnrm = (float *)realloc(pnrm, (size_t)pcap * 3 * sizeof(float));
                            }
                            if (pxyz &&
                                dw4_pose_mesh(pose, (const float *)pos,
                                              gnrm ? (const float *)gnrm : NULL, bones,
                                              (int)g->num_verts, pxyz, gnrm ? pnrm : NULL) == 0) {
                                posed_rows++;
                                pos = (const uint8_t *)pxyz;
                                if (gnrm)
                                    gnrm = (const uint8_t *)pnrm;
                            }
                        }
                    }
                    if (!pos || dw4_scene_tris(sp, g, &gt, &gnt, &why) != 0)
                        continue;
                    if (nv + g->num_verts > capv) {
                        capv = (nv + g->num_verts) * 2 + 256;
                        xyz = (float *)realloc(xyz, (size_t)capv * 3 * sizeof(float));
                        uv = (float *)realloc(uv, (size_t)capv * 2 * sizeof(float));
                        nrm = (float *)realloc(nrm, (size_t)capv * 3 * sizeof(float));
                    }
                    if (nt + gnt > capt) {
                        capt = (nt + gnt) * 2 + 256;
                        tris = (uint32_t *)realloc(tris, (size_t)capt * 3 * sizeof(uint32_t));
                    }
                    for (k = 0; k < g->num_verts; k++) {
                        float px = 0, py = 0, pz = 0, x, y, z;
                        memcpy(&x, pos + 12 * k, 4);
                        memcpy(&y, pos + 12 * k + 4, 4);
                        memcpy(&z, pos + 12 * k + 8, 4);
                        px = m[0] * x + m[1] * y + m[2] * z + m[12];
                        py = m[4] * x + m[5] * y + m[6] * z + m[13];
                        pz = m[8] * x + m[9] * y + m[10] * z + m[14];
                        xyz[3 * (nv + k)] = px;
                        xyz[3 * (nv + k) + 1] = py;
                        xyz[3 * (nv + k) + 2] = pz;
                        if (guv) {
                            memcpy(&uv[2 * (nv + k)], guv + 8 * k, 4);
                            memcpy(&uv[2 * (nv + k) + 1], guv + 8 * k + 4, 4);
                        } else {
                            uv[2 * (nv + k)] = uv[2 * (nv + k) + 1] = 0.0f;
                        }
                        /* The mesh's own vertex normals, rotated into world space.
                         * A mesh that ships none keeps a zero normal, which the shader reads as
                         * "use the face normal" -- so the smooth path is per mesh, not global. */
                        if (gnrm) {
                            float nx, ny, nz;
                            memcpy(&nx, gnrm + 12 * k, 4);
                            memcpy(&ny, gnrm + 12 * k + 4, 4);
                            memcpy(&nz, gnrm + 12 * k + 8, 4);
                            nrm[3 * (nv + k)] = m[0] * nx + m[1] * ny + m[2] * nz;
                            nrm[3 * (nv + k) + 1] = m[4] * nx + m[5] * ny + m[6] * nz;
                            nrm[3 * (nv + k) + 2] = m[8] * nx + m[9] * ny + m[10] * nz;
                        } else {
                            nrm[3 * (nv + k)] = nrm[3 * (nv + k) + 1] = nrm[3 * (nv + k) + 2] = 0.0f;
                        }
                    }
                    for (k = 0; k < gnt; k++) {
                        tris[3 * (nt + k)] = nv + gt[3 * k];
                        tris[3 * (nt + k) + 1] = nv + gt[3 * k + 1];
                        tris[3 * (nt + k) + 2] = nv + gt[3 * k + 2];
                    }
                    /* --ui-native: a small mesh placed inside the screen's own coordinate range is
                     * the front-end's 2D layer (the logo, window panels, lines, cursors), not world
                     * geometry -- so it draws in screen space (see the draw loop below). */
                    int row_ui = 0;
                    if (ui_native) {
                        float le = mesh_local_extent((const float *)pos, g->num_verts);
                        row_ui = (le > 0.0f && le <= ui_max_local && fabsf(m[12]) <= 1000.0f &&
                                  fabsf(m[13]) <= 1000.0f);
                    }
                    char drawtex[64];
                    snprintf(drawtex, sizeof(drawtex), "%s", tex0);
                    if (!drawtex[0] && deftx_ground[0]) {
                        float nrm[3];
                        mesh_mean_normal(pos, g->num_verts, gt, gnt, nrm);
                        snprintf(drawtex, sizeof(drawtex), "%s",
                                 nrm[1] > 0.5f ? deftx_ground
                                               : (deftx_wall[0] ? deftx_wall : deftx_ground));
                    }
                    if (ndraw == ncap) {
                        ncap = ncap * 2 + 64;
                        draws = (dw4_draw *)realloc(draws, (size_t)ncap * sizeof(*draws));
                    }
                    if (draws) {
                        draws[ndraw].vb = nv;
                        draws[ndraw].nv = g->num_verts;
                        draws[ndraw].tb = nt;
                        draws[ndraw].nt = gnt;
                        draws[ndraw].uvb = nv;
                        draws[ndraw].tint[0] = 1.0f;
                        draws[ndraw].tint[1] = 1.0f;
                        draws[ndraw].tint[2] = 1.0f;
                        if (have_const_tint) {
                            draws[ndraw].tint[0] = const_tint[0];
                            draws[ndraw].tint[1] = const_tint[1];
                            draws[ndraw].tint[2] = const_tint[2];
                        }
                        snprintf(draws[ndraw].texname, sizeof(draws[ndraw].texname), "%s", drawtex);
                        draws[ndraw].ui = row_ui;
                        ndraw++;
                    }
                    nv += g->num_verts;
                    nt += gnt;
                    got = 1;
                    free(gt);
                  }
                }
                if (got)
                    placed++;
                else
                    missing++;
            }
            fclose(fp);
            free(pxyz);
            free(pnrm);
            if (posed_rows)
                printf("  pose: %d mesh(es) skinned\n", posed_rows);
            if (nv && nt && (frames > 1 || have_view) && view_fov > 0.0f) {
                /* A frame run: the same geometry each frame, seen through a supplied view (a
                 * stage's own camera), turning by `spin` degrees about Y per frame -- the port
                 * drawing stage after stage of the engine's world rather than one fixed shot. */
                float tint[3];
                if (want_window || use_vk) {
                    if (use_vk) {
                        /* the Vulkan present path: SDL still makes the window and the surface, but
                         * the frame goes to the screen through a swapchain (src/vk_present.c).  With
                         * no --window there is nothing to present to, and the backend initialises
                         * the loader and a device only -- which is what the suite can check. */
                        vk = dw4_vk_open(w, h, "dw4 render", want_window ? 0 : 1);
                        if (vk) {
                            char gpu[128], fmt[64];
                            int swz = 0;
                            dw4_vk_report(vk, gpu, sizeof(gpu), fmt, sizeof(fmt), &swz);
                            printf("  vulkan: %s via %s (%s)%s\n",
                                   want_window ? "presenting" : "device only (no surface)", gpu, fmt,
                                   swz ? " [R/B swizzled]" : "");
                        } else {
                            fprintf(stderr, "  vulkan: unavailable\n");
                            if (want_window)
                                fprintf(stderr, "  vulkan: falling back to SDL\n");
                        }
                    }
                    if (want_window && !vk) {
                        /* The GL path already owns an EGL context; SDL's accelerated renderer would
                         * fight it for GL and present black, so present through SDL's software one. */
                        if (use_gl)
                            setenv("SDL_RENDER_DRIVER", "software", 1);
                        win = dw4_window_open(w, h, "dw4 render", 0);
                        printf("  window: %s\n", win ? "presenting live (SDL2)"
                                                        : "SDL2 not compiled in / driver failed");
                        if (win) {
                            int ok = dw4_window_order_ok(win);
                            printf("  window: pixel order %s\n",
                                   ok == 1 ? "ok (R,G,B,A preserved)"
                                           : (ok == 0 ? "WRONG (the present path reorders the channels)"
                                                      : "not checked"));
                        }
                    }
                }
                tint[0] = tint[1] = tint[2] = 1.0f;
                if (have_const_tint) {
                    tint[0] = const_tint[0]; tint[1] = const_tint[1]; tint[2] = const_tint[2];
                }
                int f;
                (void)tint;
                struct timespec t0, t1;
                double fps_now = 0.0, fps_last = 0.0;   /* for the --fps readout */
                clock_gettime(CLOCK_MONOTONIC, &t0);
                for (f = 0; f < frames; f++) {
                    int nui = 0;
                    float a = (float)(spin * f * 3.14159265 / 180.0), ca = cosf(a), sa = sinf(a);
                    float ry[16] = { ca,0,sa,0, 0,1,0,0, -sa,0,ca,0, 0,0,0,1 }, v2[16];
                    char path[4096];
                    int i2, j2, k2;
                    for (i2 = 0; i2 < 4; i2++)
                        for (j2 = 0; j2 < 4; j2++) {
                            float acc = 0;
                            for (k2 = 0; k2 < 4; k2++)
                                acc += viewm[4 * i2 + k2] * ry[4 * k2 + j2];
                            v2[4 * i2 + j2] = acc;
                        }
                    /* the renderer's projection divides by +z, so in-front must be v.z > 0: negate
                     * the view's third row (this is the sign convention cam_project uses) */
                    for (j2 = 0; j2 < 4; j2++)
                        v2[8 + j2] = -v2[8 + j2];
                    uint32_t d2;
                    dw4_render_set_view(v2, view_fov, view_aspect);
                    dw4_fb_clear(&fb, 18, 22, 30);
                    if (gl)
                        dw4_gl_frame_begin(gl, v2, view_fov, view_aspect, amb, rig, nrig);
                    for (d2 = 0; d2 < ndraw; d2++) {
                        /* one mesh at a time, so it carries its own tint: the view override means
                         * every call shares one camera, so nothing has to be merged */
                        const dw4_draw *dr = &draws[d2];
                        uint32_t q2;
                        if (dr->nv + 1 > scapv) {
                            scapv = dr->nv + 64;
                            sxyz = (float *)realloc(sxyz, (size_t)scapv * 3 * sizeof(float));
                            suv = (float *)realloc(suv, (size_t)scapv * 2 * sizeof(float));
                            snrm = (float *)realloc(snrm, (size_t)scapv * 3 * sizeof(float));
                        }
                        if (dr->nt + 1 > scapt) {
                            scapt = dr->nt + 64;
                            stris = (uint32_t *)realloc(stris, (size_t)scapt * 3 * sizeof(uint32_t));
                            stint = (float *)realloc(stint, (size_t)scapt * 3 * sizeof(float));
                        }
                        if (!sxyz || !stris || !stint || (gl && !suv))
                            continue;
                        for (q2 = 0; q2 < dr->nv; q2++) {
                            sxyz[3 * q2] = xyz[3 * (dr->vb + q2)];
                            sxyz[3 * q2 + 1] = xyz[3 * (dr->vb + q2) + 1];
                            sxyz[3 * q2 + 2] = xyz[3 * (dr->vb + q2) + 2];
                            if (snrm && !flat) {
                                snrm[3 * q2] = nrm[3 * (dr->vb + q2)];
                                snrm[3 * q2 + 1] = nrm[3 * (dr->vb + q2) + 1];
                                snrm[3 * q2 + 2] = nrm[3 * (dr->vb + q2) + 2];
                            }
                            if (suv) {
                                suv[2 * q2] = uv[2 * (dr->uvb + q2)];
                                suv[2 * q2 + 1] = uv[2 * (dr->uvb + q2) + 1];
                            }
                        }
                        for (q2 = 0; q2 < dr->nt; q2++) {
                            stris[3 * q2] = tris[3 * (dr->tb + q2)] - dr->vb;
                            stris[3 * q2 + 1] = tris[3 * (dr->tb + q2) + 1] - dr->vb;
                            stris[3 * q2 + 2] = tris[3 * (dr->tb + q2) + 2] - dr->vb;
                        }
                        {
                            const dw4_tex *dtex = dr->texname[0]
                                                      ? texcache_get(&tc, dr->texname)
                                                      : (have_tex ? &tex : NULL);
                            /* --ui-native: the front-end's 2D rows draw in SCREEN space -- the origin
                             * at the framebuffer centre, +x right and +y up -- through the GS UI
                             * primitive (unlit, alpha-blended, no depth), instead of the camera. */
                            if (!gl && ui_native && dr->ui) {
                                float *uvv = (float *)malloc((size_t)dr->nv * 4 * sizeof(float));
                                const uint8_t rgba[3][4] = { { 128, 128, 128, 128 },
                                                             { 128, 128, 128, 128 },
                                                             { 128, 128, 128, 128 } };
                                if (uvv) {
                                    for (q2 = 0; q2 < dr->nv; q2++) {
                                        uvv[q2 * 4 + 0] = w * 0.5f + ui_scale * sxyz[3 * q2];
                                        uvv[q2 * 4 + 1] = h * 0.5f - ui_scale * sxyz[3 * q2 + 1];
                                        uvv[q2 * 4 + 2] = suv ? suv[2 * q2] : 0.0f;
                                        uvv[q2 * 4 + 3] = suv ? suv[2 * q2 + 1] : 0.0f;
                                    }
                                    for (q2 = 0; q2 < dr->nt; q2++) {
                                        if (stris[3 * q2] >= dr->nv || stris[3 * q2 + 1] >= dr->nv ||
                                            stris[3 * q2 + 2] >= dr->nv)
                                            continue;
                                        dw4_render_ui_tri(&fb, &uvv[stris[3 * q2] * 4],
                                                          &uvv[stris[3 * q2 + 1] * 4],
                                                          &uvv[stris[3 * q2 + 2] * 4], rgba, dtex,
                                                          1);
                                    }
                                    free(uvv);
                                    nui++;
                                }
                                continue;
                            }
                            if (gl)
                                dw4_gl_frame_mesh(gl, sxyz, flat ? NULL : snrm, suv, stris,
                                                  dr->nv, dr->nt, (float *)dr->tint, dtex);
                            else if (dtex)
                                dw4_render_mesh_n(&fb, (const uint8_t *)sxyz,
                                                  flat ? NULL : (const uint8_t *)snrm,
                                                  (const uint8_t *)suv,
                                                  dr->nv, stris, dr->nt,
                                                  yaw, pitch, (float *)dr->tint, dtex);
                            else
                                dw4_render_mesh_n(&fb, (const uint8_t *)sxyz,
                                                  flat ? NULL : (const uint8_t *)snrm, NULL,
                                                  dr->nv, stris, dr->nt,
                                                  yaw, pitch, (float *)dr->tint, NULL);
                        }
                    }
                    if (gl)
                        dw4_gl_frame_end(gl, &fb);
                    if (ui_native && !gl)
                        printf("ui-native: %d row(s) drawn in screen space (scale %.3f, extent <= %.0f)\n",
                               nui, ui_scale, ui_max_local);
                    if (ui_path && !gl) {
                        /* the exporter writes its textures beside the TSV, so default there unless
                         * --uitex says otherwise (--texdir is the scene's prop-texture dir) */
                        char uitex[2048];
                        const char *ud = ui_texdir;
                        int ui_tri;
                        if (!ud) {
                            const char *slash = strrchr(ui_path, '/');
                            size_t len = slash ? (size_t)(slash - ui_path) : 1;
                            if (len >= sizeof(uitex)) len = sizeof(uitex) - 1;
                            memcpy(uitex, slash ? ui_path : ".", len);
                            uitex[len] = 0;
                            ud = uitex;
                        }
                        ui_tri = dw4_ui_draw_file(&fb, ui_path, ud, ui_threads, NULL, 1.0f, 1.0f);
                        if (ui_tri >= 0)
                            printf("ui: %d triangle(s) from %s (textures in %s)\n", ui_tri, ui_path, ud);
                        else
                            fprintf(stderr, "ui: could not read %s\n", ui_path);
                    }
                    {
                        /* the frame clock: it paces the animated layer and feeds the --fps readout */
                        struct timespec tn;
                        double el;
                        clock_gettime(CLOCK_MONOTONIC, &tn);
                        el = (tn.tv_sec - t0.tv_sec) + (tn.tv_nsec - t0.tv_nsec) / 1e9;
                        if (fps_last > 0.0 && el > fps_last) {
                            double inst = 1.0 / (el - fps_last);
                            fps_now = fps_now > 0.0 ? fps_now * 0.9 + inst * 0.1 : inst;
                        }
                        fps_last = el;
                        if (ui_seq_dir && !gl) {
                            int sn = ui_seq_draw(&fb, ui_seq_dir, ui_texdir, el, ui_seq_fps);
                            if (sn < 0 && f == 0)
                                fprintf(stderr, "ui-seq: no .tsv layers in %s\n", ui_seq_dir);
                            else if (f == 0)
                                printf("ui-seq: cycling %s at %.1f fps (has %d rows this frame)\n",
                                       ui_seq_dir, ui_seq_fps, sn);
                        }
                    }
                    if (osd_fps != 0 && (osd_fps == 1 || win || vk)) {
                        /* the readout: top-left, over a darkened plate so it stays legible over the
                         * logo (dw4_fb_text is a diagnostic font, not the game's) */
                        char osd[64];
                        int scale = 2, pad = 4, tw, th;
                        if (osd_text)
                            snprintf(osd, sizeof(osd), "%s", osd_text);
                        else
                            snprintf(osd, sizeof(osd), "%.0f fps", fps_now);
                        tw = dw4_fb_text_width(osd, scale);
                        th = 7 * scale;
                        dw4_fb_plate(&fb, 8 - pad, 8 - pad, tw + 2 * pad, th + 2 * pad, 45);
                        dw4_fb_text(&fb, 8, 8, osd, scale, 255, 255, 255);
                    }
                    if ((!win && !vk) || f == 0) {
                        snprintf(path, sizeof(path), "%s/frame_%04d.png", out_dir ? out_dir : ".", f);
                        if (dw4_png_write(path, fb.rgba, fb.w, fb.h) != 0)
                            rc = 1;
                    }
                    if (vk) {
                        if (dw4_vk_present(vk, &fb) < 0)
                            break;
                        if (!dw4_vk_pump(vk))
                            break;
                    } else if (win) {
                        dw4_window_present(win, &fb);
                        if (!dw4_window_pump(win, NULL))
                            break;
                    }
                }
                clock_gettime(CLOCK_MONOTONIC, &t1);
                {
                    double ms = (t1.tv_sec - t0.tv_sec) * 1000.0 +
                                (t1.tv_nsec - t0.tv_nsec) / 1e6;
                    printf("played %d frame(s) through the supplied view: %.1f ms total,"
                           " %.2f ms/frame, %.1f fps\n", frames, ms, ms / frames,
                           1000.0 * frames / (ms > 0 ? ms : 1));
                }
                free(xyz);
                free(uv);
                free(nrm);
                free(sxyz);
                free(suv);
                free(snrm);
                free(stint);
                free(stris);
                free(draws);
                texcache_free(&tc);
                if (gl)
                    dw4_gl_close(gl);
                return rc;
            }
            if (nv && nt) {
                float tint[3];
                tint[0] = tint[1] = tint[2] = 1.0f;
                if (have_const_tint) {
                    tint[0] = const_tint[0]; tint[1] = const_tint[1]; tint[2] = const_tint[2];
                }
                if (span > 0) {
                    /* frame a region: clamp what is drawn to a box round `cam`, so one far-flung
                     * node cannot shrink the whole stage to a dot.  With no `--cam`, the box is
                     * centred on the drawn geometry itself, so `--span` drops outliers. */
                    if (!have_clip && nv) {
                        float mn[3] = { 1e30f, 1e30f, 1e30f };
                        float mx[3] = { -1e30f, -1e30f, -1e30f };
                        uint32_t q;
                        int ax;
                        for (q = 0; q < nv; q++) {
                            for (ax = 0; ax < 3; ax++) {
                                float v = xyz[3 * q + ax];
                                if (v < mn[ax]) mn[ax] = v;
                                if (v > mx[ax]) mx[ax] = v;
                            }
                        }
                        for (ax = 0; ax < 3; ax++)
                            cam[ax] = (mn[ax] + mx[ax]) * 0.5f;
                    }
                    uint32_t *keep = (uint32_t *)malloc((size_t)nt * 3 * sizeof(uint32_t));
                    uint32_t nk = 0, t;
                    if (keep) {
                        for (t = 0; t < nt; t++) {
                            uint32_t a0 = tris[3 * t], b0 = tris[3 * t + 1], c0 = tris[3 * t + 2];
                            uint32_t vs[3] = { a0, b0, c0 };
                            int inside = 1, q;
                            for (q = 0; q < 3; q++) {
                                float vx = xyz[3 * vs[q]], vy = xyz[3 * vs[q] + 1];
                                float vz = xyz[3 * vs[q] + 2];
                                if (vx < cam[0] - span || vx > cam[0] + span ||
                                    vy < cam[1] - span || vy > cam[1] + span ||
                                    vz < cam[2] - span || vz > cam[2] + span)
                                    inside = 0;
                            }
                            if (inside) {
                                tris[3 * nk] = a0;
                                tris[3 * nk + 1] = b0;
                                tris[3 * nk + 2] = c0;
                                nk++;
                            }
                        }
                        nt = nk;
                        free(keep);
                        /* the camera fits the *vertices*, so the ones outside the box have to go
                         * too -- otherwise one far node shrinks the whole view to a dot */
                        {
                            uint32_t *map = (uint32_t *)calloc(nv, sizeof(uint32_t));
                            float *keepxyz = (float *)malloc((size_t)nv * 3 * sizeof(float));
                            float *keepuv = uv ? (float *)malloc((size_t)nv * 2 * sizeof(float))
                                               : NULL;
                            uint32_t n2 = 0, t2, q2;
                            if (map && keepxyz && (keepuv || !uv)) {
                                for (t2 = 0; t2 < nt; t2++)
                                    for (q2 = 0; q2 < 3; q2++) {
                                        uint32_t v = tris[3 * t2 + q2];
                                        if (!map[v]) {
                                            map[v] = ++n2;
                                            keepxyz[3 * (n2 - 1)] = xyz[3 * v];
                                            keepxyz[3 * (n2 - 1) + 1] = xyz[3 * v + 1];
                                            keepxyz[3 * (n2 - 1) + 2] = xyz[3 * v + 2];
                                            if (keepuv) {
                                                keepuv[2 * (n2 - 1)] = uv[2 * v];
                                                keepuv[2 * (n2 - 1) + 1] = uv[2 * v + 1];
                                            }
                                        }
                                    }
                                for (t2 = 0; t2 < nt; t2++)
                                    for (q2 = 0; q2 < 3; q2++)
                                        tris[3 * t2 + q2] = map[tris[3 * t2 + q2]] - 1;
                                free(xyz);
                                xyz = keepxyz;
                                if (keepuv) {
                                    free(uv);
                                    uv = keepuv;
                                }
                                nv = n2;
                            } else {
                                free(map);
                                free(keepxyz);
                                free(keepuv);
                            }
                            free(map);
                        }
                    }
                    printf("  framing (%g,%g,%g) +/- %g: %u triangle(s)\n", cam[0], cam[1], cam[2],
                           span, nt);
                }
                dw4_fb_clear(&fb, 18, 22, 30);
                if (gl) {
                    float gv[16];
                    const float *gvv;
                    float gfov = view_fov > 0.0f ? view_fov : DW4_SCENE_CAMERA_FOV;
                    float gaspect = have_aspect ? view_aspect : dw4_scene_camera_aspect(w, h);
                    if (have_view && view_fov > 0.0f) {
                        int kk;
                        memcpy(gv, viewm, sizeof(gv));
                        for (kk = 0; kk < 4; kk++)
                            gv[8 + kk] = -gv[8 + kk];
                        gvv = gv;
                    } else {
                        dw4_render_fit_view((const uint8_t *)xyz, nv, yaw, pitch, gv, &gfov,
                                            &gaspect);
                        gvv = gv;
                    }
                    dw4_gl_render(gl, &fb, xyz, flat ? NULL : nrm, uv, tris, nv, nt, gvv, gfov,
                                  gaspect, amb, rig, nrig, tint, have_tex ? &tex : NULL);
                } else if (wire)
                    dw4_render_wire(&fb, (const uint8_t *)xyz, nv, tris, nt, yaw, pitch, w, 200,
                                    220, 255);
                else
                    dw4_render_mesh_n(&fb, (const uint8_t *)xyz,
                                      flat ? NULL : (const uint8_t *)nrm, (const uint8_t *)uv, nv,
                                      tris, nt, yaw, pitch, tint, have_tex ? &tex : NULL);
                printf("scene %s: %u row(s) placed, %u with no mesh of that name, %u vertices,"
                       " %u triangles\n", scene_tsv, placed, missing, nv, nt);
            } else {
                printf("scene %s: no row matched a mesh name\n", scene_tsv);
            }
            free(xyz);
            free(uv);
            free(nrm);
            free(tris);
            free(sxyz);
            free(suv);
            free(snrm);
            free(stint);
            free(stris);
            free(draws);
        }
    }
fe_out:
    if (gl)
        dw4_gl_close(gl);
    if (win)
        dw4_window_close(win);
    dw4_vk_close(vk);
    if (dw4_png_write(out, fb.rgba, fb.w, fb.h) != 0)
        rc = 1;
    printf("render %s: %ux%u, %u mesh(es) drawn, %u skipped (%u with vertex normals) -> %s\n",
           f.name[0] ? f.name : f.path, (unsigned)fb.w, (unsigned)fb.h, drawn, skipped, withn, out);
    printf("  lighting: ambient (%.2f,%.2f,%.2f), %d light(s)%s\n", amb[0], amb[1], amb[2],
           nlights, nlights ? "" : " (built-in placeholder rig)");
    dw4_fb_free(&fb);
    dw4_pose_close(pose);
    dw4_scene_close(&sc);
    dw4_igfile_close(&f);
    if (have2) {
        dw4_scene_close(&sc2);
        dw4_igfile_close(&f2);
    }
    if (have_mount)
        dw4_mount_close(&mnt);
    free(tex_rgba);
    texcache_free(&tc);
    return rc;
}

int main(int argc, char **argv)
{
    const char *cmd;
    if (argc >= 2 && strcmp(argv[1], "platform") == 0) {
        /* The platform seam (porting P2.1): the igPsx2* -> generic-interface mapping
         * the engine is written against, and which of those interfaces a host build provides. */
        unsigned stubs = dw4_platform_status(argc > 2 && strcmp(argv[2], "-v") == 0);
        printf("platform seam: %u igPsx2* class(es) under %u generic interface(s); %u implemented, %u stub\n",
               dw4_nifaces, dw4_platform_ifaces(), dw4_nifaces - stubs, stubs);
        if (stubs == dw4_nifaces)
            printf("  (nothing implemented -- run `dw4asset platform -v` for the list)\n");
        return 0;
    }
    const char *label = argv[2];
    uint8_t *blob = NULL;
    size_t len = 0;
    dw4_afs afs;
    int have_afs = 0, rc = 0;

    if (argc < 3) {
        fprintf(stderr,
                "usage: dw4asset afs <archive>\n"
                "       dw4asset cat <archive> <index> <out>\n"
                "       dw4asset igb <file>|--afs A --entry N [--at OFF]\n"
                "       dw4asset records <file>|--afs A --entry N [--class NAME]\n"
                "       dw4asset reflect <file>|--afs A --entry N [--class NAME] [--limit N] [--json]\n"
                "       dw4asset refs <file>|--afs A --entry N [--id K [--dump F]] [--list [N]] [--check]\n"
                "       dw4asset texpack <file>|--afs A --entry N [--list] [--decode NAME --out F]\n"
                "       dw4asset models <file>|--afs A --entry N [--list|--tsv] [--out-dir D]\n"
                "                      [--obj ID [--out F]] [--limit N]\n"
                "       dw4asset scene <roms-dir> <name.igb>|--afs A --entry N|<file> [--list|--tsv]\n"
                "                      [--out-dir D] [--arena-out F] [--check]\n"
                "       dw4asset scene --stage <roms-dir> <stage.igb> [--ref N] (...)   the game's route\n"
                "                      [--graph]   the scene graph: igSceneInfo -> graph paths -> nodes\n"
                "       dw4asset render <file>|--afs A --entry N|--stage R <stage.igb> [--name S]\n"
                "                      [--out F.png] [--scene TSV] [--texture NAME --texentry N]\n"
                "                      [--window]  present the played frame(s) live (SDL2)\n"
                "                      [--gl] [--camera [NAME]|--view 'm0 .. m15'] [--wire]\n"
                "                      [--w N --h N] [--fog SPEC] [--light SPEC] [--lights FILE]\n"
                "                      [--one-sided|--two-sided] [--cull|--cull-front|--no-cull] [--unlit] [--per-pixel|--gouraud] [--white-tint] [--tint R,G,B]\n"
                "                      [--ui UI.TSV [--uitex DIR]]  (replay a .gs dump's 2D HUD, software path;\n"
                "                                                    a TSV starting with \"#stq\" divides per px)\n"
                "                      [--ui-seq DIR [--ui-seq-fps F]]  (cycle the front-end's animated\n"
                "                                                    layer: one captured frame per .tsv, in\n"
                "                                                    time; the menu's streams are the engine\n"
                "                                                    regenerating draws, not a transform, so\n"
                "                                                    they are replayed at the ~5 fps PCSX2's\n"
                "                                                    screenshot hotkey can capture them at)\n"
                "                      [--ui-native [SCALE] [--ui-extent PX]]  (draw the front-end's own 2D\n"
                "                                                    layer, screen space, from its small meshes)\n"
                "                      [--nearest|--bilinear] [--uv-offset U,V] [--uv-scale S]\n"
                "                      [--fps|--no-fps] [--osd-text S]  (a frame-rate readout in the\n"
                "                                                    frame's top left; on by default\n"
                "                                                    when a window presents)\n"
                "                      [--ui-threads N]               replay the UI rows on N threads\n"
                "                                                    (default: one per core; the frame's\n"
                "                                                    rows are split, so 1 == N exactly)\n"
                "                      [--vulkan]                    present through a Vulkan swapchain\n"
                "                                                    instead of SDL's renderer\n"
                "                      [--vk-device]                 bring up the Vulkan loader and a\n"
                "                                                    device only (no window), for a check\n"
                "       dw4asset manifest <NDMW.IGB>\n"
                "       dw4asset find <NDMW.IGB> <roms-dir> <name> [out]\n"
                "       dw4asset mount <roms-dir> ls [substr]|cat <name> [out]|refs <name>|check\n"
                "       dw4asset scan <roms-dir> <class>      which entries contain a class\n"
                "       dw4asset media <roms-dir> list|probe <name>|convert <name> <out>\n"
                "       dw4asset texture <src.raw> <out.png> --w W --h H --pal <pal.raw> [--bits 8|4]\n"
                "       dw4asset livetex <ram.bin> [--list|--decode NAME --out F.png]\n"
                "       dw4asset skin <ram.bin> [--list] [--palette N] [--out posed.obj [--bind F.obj]]\n"
                "       dw4asset sfp <file>|--afs A --entry N [--bank K] [--sound S] [--wav OUT]\n");
        return 2;
    }
    cmd = argv[1];
    memset(&afs, 0, sizeof(afs));

    if (strcmp(cmd, "scan") == 0 && argc >= 4)
        return cmd_scan(argv[2], argv[3]);
    if (strcmp(cmd, "chr") == 0)
        return cmd_chr(argc - 2, argv + 2);
    if (strcmp(cmd, "scene") == 0)
        return cmd_scene(argc - 2, argv + 2);
    if (strcmp(cmd, "render") == 0)
        return cmd_render(argc - 2, argv + 2);
    if (strcmp(cmd, "texture") == 0 && argc >= 4)
        return cmd_texture(argv[2], argv[3], argc, argv);
    if (strcmp(cmd, "livetex") == 0 && argc >= 3)
        return cmd_livetex(argc - 2, argv + 2);
    if (strcmp(cmd, "skin") == 0 && argc >= 3)
        return cmd_skin(argc - 2, argv + 2);
    if (strcmp(cmd, "media") == 0)
        return cmd_media(argv[2], argc >= 4 ? argv[3] : "", argc >= 5 ? argv[4] : NULL,
                         argc >= 6 ? argv[5] : NULL, argc, argv);
    if (strcmp(cmd, "mount") == 0) {
        const char *sub = argc >= 4 ? argv[3] : "";
        const char *a1 = argc >= 5 ? argv[4] : NULL;
        const char *o1 = argc >= 6 ? argv[5] : NULL;
        return cmd_mount(argv[2], sub, a1, o1);
    }
    if (strcmp(cmd, "afs") == 0)
        return cmd_afs(argv[2]);
    if (strcmp(cmd, "cat") == 0 && argc >= 5)
        return cmd_cat(argv[2], argv[3], argv[4]);

    if (strcmp(argv[2], "--afs") == 0) {
        uint32_t entry = 0;
        int i, have_entry = 0;
        if (argc < 4) {
            fprintf(stderr, "need --afs <archive> --entry N\n");
            return 2;
        }
        for (i = 4; i < argc; i++) {
            if (strcmp(argv[i], "--entry") == 0 && i + 1 < argc) {
                entry = (uint32_t)strtoul(argv[++i], NULL, 0);
                have_entry = 1;
            } else if (strcmp(argv[i], "--class") == 0 && i + 1 < argc) {
                g_class_filter = argv[++i];
            } else if (strcmp(argv[i], "--hist") == 0) {
                g_hist_all = 1;
            } else if (strcmp(argv[i], "--at") == 0 && i + 1 < argc) {
                g_at = (uint32_t)strtoul(argv[++i], NULL, 0);
            } else if (strcmp(argv[i], "--json") == 0) {
                g_json = 1;
            } else if (strcmp(argv[i], "--limit") == 0 && i + 1 < argc) {
                g_limit = (uint32_t)strtoul(argv[++i], NULL, 0);
            } else if (strcmp(argv[i], "--id") == 0 && i + 1 < argc) {
                g_ref_id = strtol(argv[++i], NULL, 0);
            } else if (strcmp(argv[i], "--list") == 0) {
                g_ref_list = (i + 1 < argc && argv[i + 1][0] != '-') ?
                             (int)strtol(argv[++i], NULL, 0) : 40;
            } else if (strcmp(argv[i], "--check") == 0) {
                g_ref_check = 1;
            } else if (strcmp(argv[i], "--dump") == 0 && i + 1 < argc) {
                g_ref_dump = argv[++i];
            }
        }
        if (!have_entry) {
            fprintf(stderr, "need --entry N\n");
            return 2;
        }
        if (dw4_afs_open(&afs, argv[3]) != 0) {
            fprintf(stderr, "cannot read %s\n", argv[3]);
            return 1;
        }
        have_afs = 1;
        blob = (uint8_t *)dw4_afs_entry_data(&afs, entry);
        if (!blob) {
            fprintf(stderr, "entry %u out of range\n", entry);
            dw4_afs_close(&afs);
            return 1;
        }
        len = afs.entries[entry].size;
        label = argv[3];
    } else {
        int i;
        for (i = 3; i < argc; i++) {
            if (strcmp(argv[i], "--class") == 0 && i + 1 < argc)
                g_class_filter = argv[++i];
            else if (strcmp(argv[i], "--hist") == 0)
                g_hist_all = 1;
            else if (strcmp(argv[i], "--at") == 0 && i + 1 < argc)
                g_at = (uint32_t)strtoul(argv[++i], NULL, 0);
            else if (strcmp(argv[i], "--json") == 0)
                g_json = 1;
            else if (strcmp(argv[i], "--limit") == 0 && i + 1 < argc)
                g_limit = (uint32_t)strtoul(argv[++i], NULL, 0);
            else if (strcmp(argv[i], "--id") == 0 && i + 1 < argc)
                g_ref_id = strtol(argv[++i], NULL, 0);
            else if (strcmp(argv[i], "--list") == 0)
                g_ref_list = (i + 1 < argc && argv[i + 1][0] != '-') ?
                             (int)strtol(argv[++i], NULL, 0) : 40;
            else if (strcmp(argv[i], "--check") == 0)
                g_ref_check = 1;
            else if (strcmp(argv[i], "--dump") == 0 && i + 1 < argc)
                g_ref_dump = argv[++i];
        }
        if (read_file(argv[2], &blob, &len) != 0) {
            fprintf(stderr, "cannot read %s\n", argv[2]);
            return 1;
        }
    }

    if (strcmp(cmd, "manifest") == 0 || strcmp(cmd, "find") == 0) {
        /* these two read the manifest themselves, so they take paths, not a blob */
        if (strcmp(cmd, "manifest") == 0) {
            int all = 0, j;
            for (j = 3; j < argc; j++)
                if (strcmp(argv[j], "--all") == 0)
                    all = 1;
            rc = cmd_manifest(blob, len, argv[2], all);
        }
        else if (argc >= 5)
            rc = cmd_find(argv[2], argv[3], argv[4], argc >= 6 ? argv[5] : NULL);
        else
            fprintf(stderr, "find needs <manifest> <roms-dir> <name> [out]\n"), rc = 2;
        free(have_afs ? NULL : blob);
        if (have_afs)
            dw4_afs_close(&afs);
        blob = NULL;
        return rc;
    }
    if (strcmp(cmd, "afs") == 0)
        rc = cmd_afs(argv[2]);
    else if (strcmp(cmd, "cat") == 0 && argc >= 5)
        rc = cmd_cat(argv[2], argv[3], argv[4]);
    else if (strcmp(cmd, "igb") == 0)
        rc = cmd_igb(blob, len, label);
    else if (strcmp(cmd, "records") == 0)
        rc = cmd_records(blob, len, label);
    else if (strcmp(cmd, "reflect") == 0)
        rc = cmd_reflect(blob, len, label);
    else if (strcmp(cmd, "refs") == 0)
        rc = cmd_refs(blob, len, label);
    else if (strcmp(cmd, "texpack") == 0)
        rc = cmd_texpack(blob, len, label, argc, argv);
    else if (strcmp(cmd, "models") == 0)
        rc = cmd_models(blob, len, label, argc, argv);
    else if (strcmp(cmd, "sfp") == 0)
        rc = cmd_sfp(blob, len, label, argc, argv);
    else
        fprintf(stderr, "unknown command %s\n", cmd), rc = 2;

    if (have_afs)
        dw4_afs_close(&afs);
    else
        free(blob);
    return rc;
}
