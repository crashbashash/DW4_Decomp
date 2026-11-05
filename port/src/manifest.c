/* manifest.c — the virtual filesystem.  See dw4/manifest.h. */
#include "dw4/manifest.h"

#include <stdlib.h>
#include <string.h>
#include <strings.h>

/* The recovered manifest schema.  A descriptor's ordinal is its slot number, and the
 * inherited slots come first (`igAdxAfsFile` derives from `igFileName`, which derives
 * from `igNamedObject`), so `_name` is slot 2 and the class's own fields follow. */
#define SLOT_NAME        2u
#define SLOT_FILE_COUNT  3u
#define SLOT_PTNUMBER    4u
#define SLOT_FILENUMBER  5u

static const dw4_igb_value *slot(const dw4_igb_record *r, uint32_t ordinal)
{
    uint32_t i;

    for (i = 0; i < r->nvalues; i++)
        if (r->values[i].ordinal == ordinal)
            return &r->values[i];
    return NULL;
}

static int push_part(dw4_manifest *m, const char *name, int count)
{
    dw4_manifest_part *p = (dw4_manifest_part *)realloc(
        m->parts, (m->nparts + 1) * sizeof(*p));
    char *copy;

    if (!p)
        return -1;
    m->parts = p;
    p = &m->parts[m->nparts];
    copy = (char *)malloc(strlen(name) + 1);
    if (!copy)
        return -1;
    strcpy(copy, name);
    p->name = copy;
    p->file_count = count;
    m->nparts++;
    return 0;
}

static char *file_path(const dw4_igb *g, uint32_t id, const char *name)
{
    char path[1024] = "";
    uint32_t off, len;
    dw4_igb_record list;
    if (dw4_igb_ref(g, id, &off, &len) == 2 && dw4_igb_decode(g, off, &list)) {
        const dw4_igb_value *count = slot(&list, 2), *data = slot(&list, 4);
        const uint8_t *block = data ? dw4_igb_block(g, data->raw, &len) : NULL;
        for (uint32_t i = 0; block && count && i < count->raw && i < len / 4; ++i) {
            const uint8_t *b = block + i * 4;
            uint32_t child = b[0] | (uint32_t)b[1]<<8 | (uint32_t)b[2]<<16 | (uint32_t)b[3]<<24;
            dw4_igb_record component;
            uint32_t ignored;
            if (dw4_igb_ref(g, child, &off, &ignored) == 2 && dw4_igb_decode(g, off, &component)) {
                if (component.name && strlen(path) + strlen(component.name) + 1 < sizeof path) {
                    strcat(path, component.name); strcat(path, "/");
                }
                dw4_igb_record_free(&component);
            }
        }
        dw4_igb_record_free(&list);
    }
    size_t n = strlen(path) + strlen(name) + 1;
    char *result = malloc(n);
    if (result) { strcpy(result, path); strcat(result, name); }
    return result;
}

static int push_file(dw4_manifest *m, const dw4_igb *g, uint32_t path,
                     const char *name, int pt, int entry)
{
    dw4_manifest_file *f = (dw4_manifest_file *)realloc(
        m->files, (m->nfiles + 1) * sizeof(*f));
    char *copy;

    if (!f)
        return -1;
    m->files = f;
    f = &m->files[m->nfiles];
    copy = (char *)malloc(strlen(name) + 1);
    if (!copy)
        return -1;
    strcpy(copy, name);
    f->name = copy;
    f->path = file_path(g, path, name);
    if (!f->path) { free(copy); return -1; }
    f->pt = pt;
    f->entry = entry;
    m->nfiles++;
    return 0;
}

int dw4_manifest_open(dw4_manifest *m, dw4_igb *g)
{
    uint32_t chain, p;

    memset(m, 0, sizeof(*m));
    if (dw4_igb_refs_open(g)) return -1;
    chain = dw4_igb_find_chain(g, 0x800);
    if (!chain)
        return -1;
    for (p = chain;;) {
        dw4_igb_record r;
        const dw4_igb_value *nm, *a, *b;

        if (!dw4_igb_decode(g, p, &r))
            break;
        nm = slot(&r, SLOT_NAME);
        if (strcmp(r.class_name, "beNDMWAfsSetupData") == 0) {
            const dw4_igb_value *fc = slot(&r, SLOT_FILE_COUNT);
            if (nm && nm->str && push_part(m, nm->str, fc ? (int)fc->raw : -1)) {
                dw4_igb_record_free(&r); dw4_manifest_close(m); return -1;
            }
        } else if (strcmp(r.class_name, "igAdxAfsFile") == 0) {
            a = slot(&r, SLOT_PTNUMBER);
            b = slot(&r, SLOT_FILENUMBER);
            if (nm && nm->str && a && b &&
                push_file(m, g, slot(&r, 3) ? slot(&r, 3)->raw : 0, nm->str,
                          (int)(int16_t)a->raw, (int)(int16_t)b->raw)) {
                dw4_igb_record_free(&r); dw4_manifest_close(m); return -1;
            }
        }
        p = r.end;
        dw4_igb_record_free(&r);
    }
    return m->nfiles ? 0 : -1;
}

void dw4_manifest_close(dw4_manifest *m)
{
    uint32_t i;

    for (i = 0; i < m->nparts; i++)
        free(m->parts[i].name);
    for (i = 0; i < m->nfiles; i++)
        { free(m->files[i].name); free(m->files[i].path); }
    free(m->parts);
    free(m->files);
    memset(m, 0, sizeof(*m));
}

const dw4_manifest_file *dw4_manifest_find(const dw4_manifest *m, const char *name)
{
    uint32_t i;

    for (i = 0; i < m->nfiles; i++)
        if (strchr(name, '/') ? !strcasecmp(m->files[i].path, name) :
                                !strcmp(m->files[i].name, name))
            return &m->files[i];
    return NULL;
}

const dw4_manifest_part *dw4_manifest_part_of(const dw4_manifest *m, int pt)
{
    if (pt < 0 || (uint32_t)pt >= m->nparts)
        return NULL;
    return &m->parts[pt];
}
