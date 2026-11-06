/* CRI AFS archive reader. Layout: offset 0 magic "AFS\0"; offset 4 u32 entry count; offset 8
 * entries[count] of { u32 offset, u32 size } (absolute file offsets); then the file data. This is
 * the port's reader, not the game's: the engine parses the same bytes in `igIGBFile`/`igFile`. */
#ifndef DW4_AFS_H
#define DW4_AFS_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint32_t offset;   /* absolute from the start of the archive */
    uint32_t size;
} dw4_afs_entry;

typedef struct {
    uint8_t *data;     /* whole archive (or its mapping), or NULL if table-only */
    size_t size;
    uint32_t count;
    dw4_afs_entry *entries;
    int owns_data;
    int mapped;        /* `data` is an mmap and must be unmapped, not freed */
} dw4_afs;

/* Read the entry table.  `path` is opened and its whole contents loaded (the
 * archives are hundreds of MB, so `afs_open_table` exists for a table-only view). */
int  dw4_afs_open(dw4_afs *a, const char *path);
int  dw4_afs_open_table(dw4_afs *a, const char *path);

/* The same, but mapping the file instead of reading it.  An AFS is 500-727 MB and a
 * caller usually wants a few entries, so the mount layer uses this: a lookup touches
 * the entry table's pages and nothing else.  Falls back to `dw4_afs_open` where there
 * is no mmap. */
int  dw4_afs_open_mmap(dw4_afs *a, const char *path);
void dw4_afs_close(dw4_afs *a);

/* A view of one entry's bytes inside the archive.  NULL when the entry is out of
 * range or the archive was opened table-only. */
const uint8_t *dw4_afs_entry_data(const dw4_afs *a, uint32_t index);

/* Write one entry to a file.  Returns the byte count, or -1. */
long dw4_afs_extract(const dw4_afs *a, uint32_t index, const char *out_path);

/* True when `buf` starts with the AFS magic. */
int  dw4_afs_is_archive(const uint8_t *buf, size_t len);

#endif /* DW4_AFS_H */
