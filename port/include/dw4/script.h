/* Original Lua 4.0.1 chunks; engine services own waits, not Lua coroutines. */
#ifndef DW4_SCRIPT_H
#define DW4_SCRIPT_H
#include <stddef.h>
#include <stdint.h>
#include "dw4/igb.h"
typedef struct dw4_script dw4_script;
typedef enum { DW4_SCRIPT_NIL, DW4_SCRIPT_NUMBER, DW4_SCRIPT_STRING, DW4_SCRIPT_OBJECT } dw4_script_type;
typedef enum {DW4_SCRIPT_PROPERTY_FOLDER=1,DW4_SCRIPT_DATABASE} dw4_script_object_kind;
/* Borrowed native identity. owner is the lifetime domain to invalidate before
 * destroying native storage. Objects are opaque tagged Lua userdata. */
typedef struct {dw4_script_object_kind kind;const void *pointer,*owner;} dw4_script_object;
typedef struct {
    dw4_script_type type;
    double number;
    const char *string; /* borrowed string; OBJECT uses the typed helpers below
                        * to share this pointer-sized ABI slot, never Lua text */
    size_t length;
} dw4_script_value;
static inline dw4_script_value dw4_script_object_value(const dw4_script_object *object)
{return object?(dw4_script_value){DW4_SCRIPT_OBJECT,0,(const char *)object,0}:(dw4_script_value){0};}
static inline const dw4_script_object *dw4_script_value_object(const dw4_script_value *value)
{return value && value->type==DW4_SCRIPT_OBJECT?(const dw4_script_object *)value->string:NULL;}
/* Existing Lua references become invalid without dereferencing native storage.
 * Identity cache entries live until VM reset/close; invalidation never executes Lua. */
void dw4_script_objects_invalidate(dw4_script *,const void *owner);
/* Return 0 on success, -1 with a diagnostic on unsupported/failed services.
 * Arguments exclude be/self. Numeric 0 remains Lua 4's truthy numeric 0.
 * Return values (including boolean engine results) retain their retail type. */
typedef int (*dw4_script_binding)(void *user, const char *method,
    const dw4_script_value *args, size_t nargs, dw4_script_value *result,
    char *error, size_t error_cap);
dw4_script *dw4_script_open(dw4_script_binding binding, void *user);
void dw4_script_close(dw4_script *s);
const char *dw4_script_error(const dw4_script *s);
/* Retail collection order, independent of host scope tokens. Each info keeps
 * its ordered rows; execution uses the first matching row in every info.
 * Bytes and names are copied. Pack collection follows beLuaInfo._dataList,
 * never all beLuaData records indiscriminately; publication is transactional.
 * Collection switches run/dofile to retail lookup. Legacy scoped cache
 * loaders remain a separate API and do not participate in retail lookup. */
typedef struct { const char *name; const void *bytes; size_t size; } dw4_script_buffer;
int dw4_script_collect_info(dw4_script *,const dw4_script_buffer *,size_t);
int dw4_script_collect_pack(dw4_script *,dw4_igb *);
/* Optional host lifetime tag; does not change retail execution precedence. */
int dw4_script_collect_pack_scoped(dw4_script *,uint64_t,dw4_igb *);
/* Optional mounted-file fallback. Return 0 with borrowed bytes, 2 for absent,
 * or -1 for a read failure. Bytes must remain valid until run_named returns.
 * The first [EOF] terminates source. No host filesystem access is implicit.
 * Directory overrides affect fallback only. Returns the last buffer status,
 * falling back only on -1; errors do not stop later infos. */
typedef int (*dw4_script_source)(void *,const char *,const void **,size_t *);
void dw4_script_source_set(dw4_script *,dw4_script_source,void *,const char *directory);
/* Nonzero when a collected info pack carries a chunk of this name (no fallback source is consulted). */
int dw4_script_has_info(const dw4_script *,const char *name);
int dw4_script_run_named(dw4_script *,const char *name,const char *directory);
/* Whole-VM cleanup, only between calls. Recreate preserves collected infos
 * for loader phase 3; remove_all releases those too and leaves no live VM.
 * Recreate clears arbitrary globals and scoped closures, preserving bindings.
 * remove_all also clears the mounted source and fallback directory. */
int dw4_script_busy(const dw4_script *);
int dw4_script_recreate(dw4_script *);
int dw4_script_remove_all(dw4_script *);
/* Load only, in session scope zero. Duplicate names in that scope replace closures. */
int dw4_script_load(dw4_script *s, const char *name, const void *chunk, size_t size);
/* Resolve beLuaData -> beLuaDataObject -> memory pool; no magic/name scans.
 * Loading a stage pack is transactional: failure preserves previous closures. */
int dw4_script_load_pack(dw4_script *s, dw4_igb *g);
/* Load one named closure through the same validated beLuaData reference chain. */
int dw4_script_load_pack_named(dw4_script *,dw4_igb *,const char *);
/* Host ownership: latest successful publication wins by name. Each scope
 * retains one closure per name; removing it restores any older owner. Failed
 * loads preserve every owner. Scope zero is valid and used by legacy loaders.
 * Removal during a call is safe; the executing Lua stack retains its closure.
 * This releases named-cache refs only, not globals/side effects from execution. */
int dw4_script_load_scoped(dw4_script *,uint64_t scope,const char *,const void *,size_t);
int dw4_script_load_pack_scoped(dw4_script *,uint64_t scope,dw4_igb *);
int dw4_script_load_pack_named_scoped(dw4_script *,uint64_t scope,dw4_igb *,const char *);
void dw4_script_remove_scope(dw4_script *,uint64_t scope);
int dw4_script_run(dw4_script *s, const char *name);
int dw4_script_call(dw4_script *s, const char *global,
                    const dw4_script_value *args, size_t nargs);
int dw4_script_set(dw4_script *s, const char *global, dw4_script_value value);
int dw4_script_get(dw4_script *s, const char *global, dw4_script_value *value);
/* Inspect original chunk boundaries without trusting lengths in malformed data. */
int dw4_script_chunk_size(const void *chunk, size_t available, size_t *size);
#endif
