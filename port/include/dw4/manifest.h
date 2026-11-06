/* dw4/manifest.h — the virtual filesystem: NDMW.IGB's name → archive entry table.
 *
 * `NDMW.IGB` (106 KB) is the game's root manifest.  Decoded as igBinary it is a small
 * schema of 20 classes, and two of them carry the whole filesystem:
 *
 *   beNDMWAfsSetupData   `_name` "ndmw.afs" / "area.afs", `_fileCount` 972 / 1382
 *   igAdxAfsFile         `_name` (the file's name), `_ptNumber` (which archive),
 *                        `_fileNumber` (which entry in it)
 *
 * Measured: `igAdxAfsFile` (`NDMW.IGB`, 2,081 records) gives 2,080 names, `_ptNumber` 0
 * = `ndmw.afs` (697 of its 972 entries) and 1 = `area.afs` (all 1,382).  The mapping is
 * checkable and checked — `_ptNumber` 0 `_fileNumber` 140 is `stag0102.igb`, which
 * identified as AFS entry 140 — and `(pt 1, entry 0)` is
 * `aeu_opening.sfd`, matching AREA.AFS entry 0 being MPEG.
 *
 * The descriptors the reader uses are ordinal-based, and the ordinals are part of the
 * recovered manifest schema (`igAdxAfsFile` base is `igFileName`, so `_name` is the
 * inherited `igNamedObject` slot 2).
 */
#ifndef DW4_MANIFEST_H
#define DW4_MANIFEST_H

#include <stdint.h>

#include "dw4/igb.h"

typedef struct {
    char *name;            /* "ndmw.afs", "area.afs" */
    int file_count;        /* the archive's entry count, as the manifest states it */
} dw4_manifest_part;

typedef struct {
    char *name;            /* the file's name inside the archive */
    char *path;            /* inherited igFileName._pathList plus basename */
    int pt;                /* 0 = ndmw.afs, 1 = area.afs (index into `parts`) */
    int entry;             /* AFS entry index; -1 is the manifest's "NONE" sentinel */
} dw4_manifest_file;

typedef struct {
    dw4_manifest_part *parts;
    uint32_t nparts;
    dw4_manifest_file *files;
    uint32_t nfiles;
} dw4_manifest;

/* Decode the table.  Returns 0 on success; the manifest borrows nothing, it copies. */
int  dw4_manifest_open(dw4_manifest *m, dw4_igb *g);
void dw4_manifest_close(dw4_manifest *m);

/* Basenames retain exact lookup; directory-qualified paths ignore case. */
const dw4_manifest_file *dw4_manifest_find(const dw4_manifest *m, const char *name);

/* The archive a file's `pt` refers to, or NULL. */
const dw4_manifest_part *dw4_manifest_part_of(const dw4_manifest *m, int pt);

#endif /* DW4_MANIFEST_H */
