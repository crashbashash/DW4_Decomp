/* The game arena. One contiguous host allocation addressed by 32-bit offsets (`dw4_handle`, 0 =
 * NULL, payloads 16-byte aligned), holding the decomp's structs byte for byte (the field offsets
 * in reflected.h are the authority). Two regions: persistent: grows up from DW4_ARENA_BASE, blocks
 * are freed individually and reused (exact size classes, no coalescing); stage: grows down from
 * the end, released as a whole by dw4_arena_stage_reset, which reports the blocks still live.
 * Every access goes through a handle accessor that checks the handle; a host pointer is never
 * stored in the arena. Allocation failure returns a NULL handle and records a status the caller
 * must act on. Reference counting follows the engine's inline idiom (`--refs; if ((refs &
 * 0x7fffff) == 0) igObject_Destroy(o)`; igObject_Destroy 0x2ff820 runs the destructor slots 08, 10
 * and 00, then frees the buffer). The class registry maps a retail vtable word to a class (name,
 * instance size, parent) and its host method table, so retargeted code keeps the original virtual
 * dispatch. Slot function pointers are opaque here: the caller casts to the slot's documented
 * signature. */
#ifndef DW4_ARENA_H
#define DW4_ARENA_H

#include <stddef.h>
#include <stdint.h>

#include "dw4/scene.h"   /* dw4_handle */

#define DW4_ARENA_RETAIL_BYTES (32u * 1024u * 1024u)
#define DW4_ARENA_ALIGN        16u
#define DW4_ARENA_BASE         0x1000u   /* handle 0 is NULL, so the first block starts here (as the scene arena) */

typedef enum { DW4_REGION_PERSISTENT = 0, DW4_REGION_STAGE = 1 } dw4_region;

typedef enum {
    DW4_ARENA_OK = 0,
    DW4_ARENA_EXHAUSTED,    /* no room for the request */
    DW4_ARENA_BAD_SIZE,     /* zero or oversized request */
    DW4_ARENA_BAD_HANDLE,   /* NULL, misaligned, outside the arena, or not a block start */
    DW4_ARENA_NOT_LIVE,     /* the block was already freed (double free, stale handle) */
    DW4_ARENA_TOO_SMALL,    /* the access is larger than the block */
    DW4_ARENA_BAD_CLASS,    /* unknown or unregistered class / vtable word */
    DW4_ARENA_COUNT_RANGE   /* reference count would leave 1..0x7fffff */
} dw4_arena_status;

typedef struct dw4_arena dw4_arena;

/* Open an arena of `bytes` (0 = DW4_ARENA_RETAIL_BYTES). The host must be little-endian (checked). Returns NULL and writes
 * `error` on failure. */
dw4_arena *dw4_arena_open(size_t bytes, char *error, size_t cap);
void dw4_arena_close(dw4_arena *);

/* Allocate `bytes` zero-filled in a region; the NULL handle on failure (dw4_arena_status says why). */
dw4_handle dw4_arena_alloc(dw4_arena *, dw4_region, uint32_t bytes);
/* Free one block (persistent: reusable; stage: counted dead, space returns at the stage reset). */
int dw4_arena_free(dw4_arena *, dw4_handle);
/* The host pointer of a live block start, valid for `bytes` bytes; NULL otherwise. Not stored anywhere. */
void *dw4_arena_at(dw4_arena *, dw4_handle, uint32_t bytes);
/* Release the whole stage region; returns how many of its blocks were still live (leaks). Their handles become invalid. */
uint32_t dw4_arena_stage_reset(dw4_arena *);

uint32_t dw4_arena_live(const dw4_arena *, dw4_region);     /* live blocks */
uint32_t dw4_arena_used(const dw4_arena *, dw4_region);     /* bytes taken from the arena (headers included) */
dw4_arena_status dw4_arena_status_last(const dw4_arena *);  /* status of the last failing call */
const char *dw4_arena_status_text(dw4_arena_status);

/* A typed view of a live block start: NULL unless the block holds at least sizeof(Class) bytes. */
#define DW4_ARENA_OBJ(arena, Class, handle) ((Class *)dw4_arena_at((arena), (handle), (uint32_t)sizeof(Class)))

/* The session arena: one process-wide, retail-sized game arena shared by every owner of game state
 * (databases, player records, stage objects), so state can move between owners by handle. Created
 * on first use with the schema's classes registered; NULL on failure. Owners allocate in its
 * persistent region and release what they allocated when they close (dw4_arena_owned);
 * dw4_arena_live shows what is still held. dw4_session_arena_close is for tests and orderly
 * shutdown. */
dw4_arena *dw4_session_arena(void);
void dw4_session_arena_close(void);

/* The blocks one owner allocated, so it can give them all back. */
typedef struct {
    dw4_handle *h;
    uint32_t n, cap;
} dw4_arena_owned;
int dw4_arena_owned_add(dw4_arena_owned *, dw4_handle);
void dw4_arena_owned_move(dw4_arena_owned *to, dw4_arena_owned *from);   /* appends `from` to `to` and empties `from` */
void dw4_arena_owned_release(dw4_arena *, dw4_arena_owned *);            /* frees every block, then empties the list */

/* ---- the class registry ---------------------------------------------------------------------------------------------- */

typedef void (*dw4_slot_fn)(void);
/* The destructor slots igObject_Destroy runs, in order, and the signature a registered destructor has. */
#define DW4_SLOT_DESTRUCT_A 8u
#define DW4_SLOT_DESTRUCT_B 10u
#define DW4_SLOT_DESTRUCT_C 0u
typedef void (*dw4_destruct_fn)(dw4_arena *, dw4_handle);

/* Register a class by retail vtable word. `parent` is its parent's vtable word (0 = none); `size` its instance bytes. 0, or -1
 * (full / duplicate / bad). */
int dw4_class_register(dw4_arena *, uint32_t vtable, const char *name, uint32_t parent, uint32_t size);
/* Register every class of the generated schema (dw4_metaobjects) whose vtable is known; returns how many. */
int dw4_class_register_schema(dw4_arena *);
int dw4_class_set_slot(dw4_arena *, uint32_t vtable, unsigned slot, dw4_slot_fn);
/* The slot's function, inherited from the nearest ancestor that sets it; NULL when none does. */
dw4_slot_fn dw4_class_slot(const dw4_arena *, uint32_t vtable, unsigned slot);
int dw4_class_is(const dw4_arena *, uint32_t vtable, uint32_t ancestor);   /* 1 when `vtable` is `ancestor` or derives from it */
const char *dw4_class_name(const dw4_arena *, uint32_t vtable);            /* NULL when unknown */
uint32_t dw4_class_size(const dw4_arena *, uint32_t vtable);               /* 0 when unknown */

/* ---- objects ---------------------------------------------------------------------------------------------------------- */

/* A new instance of a registered class: zero-filled, header stamped as igObject_InitHeader does (count 1) and the class's vtable
 * word at +0. The NULL handle on failure. */
dw4_handle dw4_arena_object_new(dw4_arena *, dw4_region, uint32_t vtable);
int dw4_arena_object_addref(dw4_arena *, dw4_handle);            /* the new count, or -1 */
int dw4_arena_object_release(dw4_arena *, dw4_handle);           /* the new count (0 = destroyed), or -1 */
int dw4_arena_object_refcount(dw4_arena *, dw4_handle);          /* the 23-bit count, or -1 */
uint32_t dw4_arena_object_vtable(dw4_arena *, dw4_handle);       /* the object's vtable word, or 0 */
int dw4_arena_object_is(dw4_arena *, dw4_handle, uint32_t vtable);   /* 1 when the object's class is or derives from `vtable` */

#endif
