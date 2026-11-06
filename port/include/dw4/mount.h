/* dw4/mount.h — the asset tree: the root manifest plus the archives it names.
 *
 * `NDMW.IGB` names every file and says which archive holds it (`_ptNumber` 0 =
 * `NDMW.AFS`, 1 = `AREA.AFS`), so a directory of the two extracted archives plus the
 * manifest is a *filesystem*: a name resolves to bytes, and a stage's own `[<pt>.<entry>]`
 * pack references resolve through the same table.
 *
 * The archives are 727 MB and 511 MB, so they are **mapped**, not read: a lookup touches
 * the entry table and the one entry it needs.
 */
#ifndef DW4_MOUNT_H
#define DW4_MOUNT_H

#include <stddef.h>
#include <stdint.h>

#include "dw4/afs.h"
#include "dw4/manifest.h"

#define DW4_MOUNT_MAXPARTS 8

/* A `[<pt>.<entry>]` reference found inside a pack (a stage file's pack list). */
typedef struct {
    int pt;
    int entry;
    uint32_t off;      /* where the text sits, for reporting */
} dw4_ref;

typedef struct {
    uint8_t *manifest_blob;
    dw4_manifest man;
    dw4_afs parts[DW4_MOUNT_MAXPARTS];
    int nparts;
} dw4_mount;

/* `roms_dir` must hold NDMW.IGB and the archives it names (case-insensitively). */
int  dw4_mount_open(dw4_mount *m, const char *roms_dir);
void dw4_mount_close(dw4_mount *m);

/* Resolve a name to an entry's bytes (borrowed mapping), or NULL. */
const uint8_t *dw4_mount_data(const dw4_mount *m, const char *name, uint32_t *size);
/* The same, by the (part, entry) a reference carries. */
const uint8_t *dw4_mount_entry(const dw4_mount *m, int pt, int entry, uint32_t *size, uint32_t *bytes);

/* Every `[<pt>.<entry>]` occurrence in a blob, in order.  Returns the count; fills up
 * to `cap`.  This is how a stage's pack list is read without decoding the record that
 * owns the strings (the notation itself is the recovered fact). */
uint32_t dw4_mount_scan_refs(const uint8_t *blob, size_t size, dw4_ref *out, uint32_t cap);

#endif /* DW4_MOUNT_H */
