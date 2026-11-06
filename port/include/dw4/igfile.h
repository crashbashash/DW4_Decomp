/* dw4/igfile.h — the host file seam (porting task P2.3).
 *
 * The game reads its assets through `igFile`: something with a size, a read and a "give me the
 * whole thing" call.  On the PS2 that sits on the SDK's file API plus the IOP; here it sits on
 * POSIX.  Three ways in, all producing the same borrow-able buffer:
 *
 *   dw4_igfile_open_path()   a plain host file
 *   dw4_igfile_open_afs()    one entry of an AFS archive, borrowed from a mapping
 *   dw4_igfile_open_named()  a name the manifest resolves (`stag0102.igb`) — the engine-shaped
 *                            route, through the mounted tree (P3.2)
 *
 * A file is *mapped*, not slurped, wherever the platform allows: the archives are 727 MB and
 * 511 MB, and a loader that copies a whole one is not a loader anyone can run.  `data` therefore
 * points at a mapping (or at the mount's own mapping for an entry) and is only freed when this
 * seam allocated it — `owned` says which.
 *
 * This is deliberately *only* the file seam.  Directory listing, the manifest, the archives and
 * the name -> bytes rule are the asset tree's job (dw4/mount.h); a caller that wants to load a
 * game asset by name uses `dw4_igfile_open_named` and never sees an archive index.
 */
#ifndef DW4_IGFILE_H
#define DW4_IGFILE_H

#include <stddef.h>
#include <stdint.h>

#include "dw4/mount.h"

#define DW4_IGFILE_PATH 512
#define DW4_IGFILE_NAME 128

typedef struct {
    char path[DW4_IGFILE_PATH];   /* where the bytes came from (the archive, for an entry) */
    char name[DW4_IGFILE_NAME];   /* the game-visible name, when opened by name ("" otherwise) */
    const uint8_t *data;          /* the whole content: a mapping, borrowed */
    size_t len;
    void *map;                    /* the mapping to unmap, or NULL */
    size_t map_len;
    void *afs;                    /* the archive view to close, when opened by entry */
    uint8_t *owned;               /* malloc'd content to free, or NULL */
} dw4_igfile;

int dw4_igfile_open_path(dw4_igfile *f, const char *path);
int dw4_igfile_open_afs(dw4_igfile *f, const char *afs_path, uint32_t entry);
/* `name` is a manifest name (`stag0102.igb`, `NDMW.AFS`, ...); the mount supplies the bytes. */
int dw4_igfile_open_named(dw4_igfile *f, dw4_mount *m, const char *name);

/* The engine's own route to a stage's pack: a stage file carries its pack list as
 * `[<pt>.<entry>]` text, so `index` names the n-th of them.  This is how the game
 * reaches its sound pack and its model pack -- by pointing at them from the stage file, not by an
 * archive index.  `dw4_igfile_stage_refs` reports the list without opening anything. */
uint32_t dw4_igfile_stage_refs(dw4_mount *m, const char *stage, dw4_ref *out, uint32_t cap);
int dw4_igfile_open_stage_ref(dw4_igfile *f, dw4_mount *m, const char *stage, uint32_t index);
/* Resolve the stage's beFileListInfo._fnames list in authored order. support=1
 * selects /s rows; support=0 selects scene rows. Unlike stage_refs, unrelated
 * bracket strings and physical string order do not choose a pack. */
int dw4_igfile_open_stage_pack(dw4_igfile *,dw4_mount *,const char *stage,int support,uint32_t index);
void dw4_igfile_close(dw4_igfile *f);

size_t dw4_igfile_size(const dw4_igfile *f);
const uint8_t *dw4_igfile_data(const dw4_igfile *f);

/* `igFile::Read(off, dst, n)`.  Returns 0 on success, -1 when the range is not in the file. */
int dw4_igfile_read(const dw4_igfile *f, uint32_t off, void *dst, size_t n);

#endif /* DW4_IGFILE_H */
