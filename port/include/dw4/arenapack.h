/* dw4/arenapack.h — a pack's objects as typed instances in the game arena (porting P1 of docs/arena-object-model.md).
 *
 * Each pack object becomes an arena block laid out as the decomp's struct for its class (include/dw4/reflected.h: values at the
 * reflected offsets, the engine's header from igObject_InitHeader, the class's vtable word at +0). Reference fields (descriptor type
 * 0 object ids, type 7 pool-block ids) are rewritten from the pack's ids into four-byte arena handles, string fields become handles
 * to NUL-terminated arena blocks, and every pool block is copied into an arena block. A NULL id (0xffffffff), or one the pack does
 * not define, becomes the NULL handle. Nothing in the arena points back into the pack, so the pack and its mount can be released.
 *
 * Unlike dw4_scene (a render-oriented view of a stage pack), these are the game's own typed objects, the ones the retargeted
 * matched C reads. */
#ifndef DW4_ARENAPACK_H
#define DW4_ARENAPACK_H

#include <stddef.h>
#include <stdint.h>

#include "dw4/arena.h"
#include "dw4/igb.h"

typedef struct {
    dw4_handle *map;      /* [nids] pack id -> arena handle (0 = not loaded) */
    uint32_t nids;
    uint32_t objects, blocks, strings, skipped;   /* what was loaded; `skipped` = ids with no usable record */
    dw4_arena_owned owned;                        /* every arena block the load allocated (objects, pool blocks, strings) */
} dw4_arena_pack;

/* Load every object and pool block of `g` (its id tables must be open: dw4_igb_refs_open) into `region`. 0, or -1 with `error`
 * written (the arena is left with whatever was allocated; the caller releases the region). */
int dw4_arena_pack_load(dw4_arena *, dw4_region, const dw4_igb *g, dw4_arena_pack *out, char *error, size_t cap);
/* The same, but only the objects and blocks the `roots` ids reach: through reference fields and through the elements of object lists
 * (`igObjectList` family). Ids outside the closure map to the NULL handle. */
int dw4_arena_pack_load_from(dw4_arena *, dw4_region, const dw4_igb *g, const uint32_t *roots, size_t nroots, dw4_arena_pack *out,
                             char *error, size_t cap);
/* Only the `roots` themselves: strings and values are loaded, but every reference field (and an object list's elements) is the NULL
 * handle. For info records whose referents the asset layer still reads from the pack. */
int dw4_arena_pack_load_roots(dw4_arena *, dw4_region, const dw4_igb *g, const uint32_t *roots, size_t nroots, dw4_arena_pack *out,
                              char *error, size_t cap);
/* Free the id map. The arena blocks stay until the owner releases `owned` (dw4_arena_owned_move / dw4_arena_owned_release). */
void dw4_arena_pack_free(dw4_arena_pack *);
/* Give back every block the load allocated, then free the pack's own memory. */
void dw4_arena_pack_release(dw4_arena *, dw4_arena_pack *);
/* The arena handle of a pack id, or the NULL handle. */
dw4_handle dw4_arena_pack_handle(const dw4_arena_pack *, uint32_t id);

#endif
