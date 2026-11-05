/* mount.c — the asset tree.  See dw4/mount.h. */
#include "dw4/mount.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int read_all(const char *path, uint8_t **out, size_t *out_len)
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

/* The manifest spells its archives lower-case ("ndmw.afs"); the extracted files are
 * usually upper-case, so try both. */
static int open_part(dw4_afs *a, const char *dir, const char *part)
{
    size_t i, n = strlen(part), d = strlen(dir);
    char *path = (char *)malloc(d + n + 2);
    int rc;

    if (!path)
        return -1;
    memcpy(path, dir, d);
    path[d] = '/';
    memcpy(path + d + 1, part, n + 1);
    rc = dw4_afs_open_mmap(a, path);
    if (rc == 0) {
        free(path);
        return 0;
    }
    for (i = 0; i < n; i++)
        path[d + 1 + i] = (char)toupper((unsigned char)part[i]);
    rc = dw4_afs_open_mmap(a, path);
    free(path);
    return rc;
}

int dw4_mount_open(dw4_mount *m, const char *roms_dir)
{
    char *path;
    size_t len = 0, d = strlen(roms_dir);
    dw4_igb g;
    uint32_t i;

    memset(m, 0, sizeof(*m));
    path = (char *)malloc(d + 10);
    if (!path)
        return -1;
    memcpy(path, roms_dir, d);
    memcpy(path + d, "/NDMW.IGB", 10);
    if (read_all(path, &m->manifest_blob, &len) != 0) {
        free(path);
        return -1;
    }
    free(path);
    if (dw4_igb_open(&g, m->manifest_blob, len, 0) != 0) {
        dw4_mount_close(m);
        return -1;
    }
    if (dw4_manifest_open(&m->man, &g) != 0) {
        dw4_igb_close(&g);
        dw4_mount_close(m);
        return -1;
    }
    dw4_igb_close(&g);
    m->nparts = (int)(m->man.nparts < DW4_MOUNT_MAXPARTS ? m->man.nparts : DW4_MOUNT_MAXPARTS);
    for (i = 0; i < (uint32_t)m->nparts; i++) {
        if (open_part(&m->parts[i], roms_dir, m->man.parts[i].name) != 0) {
            fprintf(stderr, "mount: cannot open %s/%s\n", roms_dir, m->man.parts[i].name);
            dw4_mount_close(m);
            return -1;
        }
    }
    return 0;
}

void dw4_mount_close(dw4_mount *m)
{
    int i;

    for (i = 0; i < m->nparts; i++)
        dw4_afs_close(&m->parts[i]);
    dw4_manifest_close(&m->man);
    free(m->manifest_blob);
    memset(m, 0, sizeof(*m));
}

const uint8_t *dw4_mount_entry(const dw4_mount *m, int pt, int entry, uint32_t *size,
                               uint32_t *bytes)
{
    const uint8_t *p;

    if (pt < 0 || pt >= m->nparts || entry < 0 || (uint32_t)entry >= m->parts[pt].count)
        return NULL;
    p = dw4_afs_entry_data(&m->parts[pt], (uint32_t)entry);
    if (p) {
        if (size)
            *size = m->parts[pt].entries[entry].size;
        if (bytes)
            *bytes = m->parts[pt].entries[entry].size;
    }
    return p;
}

const uint8_t *dw4_mount_data(const dw4_mount *m, const char *name, uint32_t *size)
{
    const dw4_manifest_file *f = dw4_manifest_find(&m->man, name);

    if (!f)
        return NULL;
    return dw4_mount_entry(m, f->pt, f->entry, size, NULL);
}

uint32_t dw4_mount_scan_refs(const uint8_t *blob, size_t size, dw4_ref *out, uint32_t cap)
{
    uint32_t n = 0;
    size_t i = 0;

    while (i + 5 < size) {
        size_t j;
        int pt = 0, entry = 0, digits;

        if (blob[i] != '[')
            goto next;
        j = i + 1;
        digits = 0;
        while (j < size && isdigit((unsigned char)blob[j])) {
            if (digits >= 6)    /* a real reference is [pt.entry] with small numbers; a long digit run is not one (and would overflow) */
                goto next;
            pt = pt * 10 + (blob[j] - '0');
            j++;
            digits++;
        }
        if (!digits || j >= size || blob[j] != '.')
            goto next;
        j++;
        digits = 0;
        while (j < size && isdigit((unsigned char)blob[j])) {
            if (digits >= 6)
                goto next;
            entry = entry * 10 + (blob[j] - '0');
            j++;
            digits++;
        }
        if (!digits || j >= size || blob[j] != ']')
            goto next;
        if (out && n < cap) {
            out[n].pt = pt;
            out[n].entry = entry;
            out[n].off = (uint32_t)i;
        }
        n++;
        i = j + 1;
        continue;
next:
        i++;
    }
    return n;
}
