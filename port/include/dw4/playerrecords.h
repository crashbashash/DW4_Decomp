/* Session-owned GAMERAM folders. Host ownership never occupies guest fields. */
#ifndef DW4_PLAYERRECORDS_H
#define DW4_PLAYERRECORDS_H
#include "dw4/script.h"
#include "dw4/arena.h"
typedef struct dw4_property_folder dw4_property_folder;
typedef struct dw4_playerrecords dw4_playerrecords;
dw4_playerrecords *dw4_playerrecords_open(void);
/* Complete private image for destination-startup transactions. Copies all nine
 * payload kinds and nested folders, restoring common -> player-zero BASE_*
 * aliases inside the new owner. Shares no payloads or Lua identities. Caller
 * owns the result; any failure leaves the source untouched. */
dw4_playerrecords *dw4_playerrecords_snapshot(const dw4_playerrecords *);
void dw4_playerrecords_close(dw4_playerrecords *);
/* Retail 3fca88..3fcb78: GETCOMMON and GETPLAYER[1..4], zero-based
 * GETPLAYER integer argument. Invalid indices fail instead of aliasing slot 0.
 * Borrowed folders survive scene/VM recreation until the session is destroyed. */
dw4_property_folder *dw4_playerrecords_get(dw4_playerrecords *,const char *method,int32_t player);
/* Named records use strcmp, as 3022c0/3a9220. Setters copy their input and
 * preserve an existing record's type. No inferred defaults from 4cedf8. */
int dw4_property_number(dw4_property_folder *,const char *,int32_t *);
const char *dw4_property_string(const dw4_property_folder *,const char *);
int dw4_property_set_number(dw4_property_folder *,const char *,int32_t);
int dw4_property_set_string(dw4_property_folder *,const char *,const char *);
int dw4_property_set_array(dw4_property_folder *,const char *,const int32_t *,size_t);
const int32_t *dw4_property_array(const dw4_property_folder *,const char *,size_t *);
/* Actual byte/float payloads for the remaining retail templates. Float values
 * retain their 32-bit bit patterns, including signed zero; setters own copies. */
int dw4_property_set_bytes(dw4_property_folder *,const char *,const uint8_t *,size_t);
const uint8_t *dw4_property_bytes(const dw4_property_folder *,const char *,size_t *);
int dw4_property_set_floats(dw4_property_folder *,const char *,const float *,size_t);
const float *dw4_property_floats(const dw4_property_folder *,const char *,size_t *);
typedef enum {DW4_PROPERTY_NUMBER,DW4_PROPERTY_STRING,DW4_PROPERTY_ARRAY,
    DW4_PROPERTY_FOLDER,DW4_PROPERTY_STRINGS,DW4_PROPERTY_UNICODES,
    DW4_PROPERTY_ITEMS,DW4_PROPERTY_BYTES,DW4_PROPERTY_FLOATS} dw4_property_type;
/* Borrow a recovered beDataObj* record for retargeted game code. Wrong/missing
 * types return {0}. Resolve fields through arena accessors, never as host
 * pointers. Reacquire after any folder mutation/publication or owner teardown;
 * this reference neither retains the record nor permits concurrent mutation. */
typedef struct {dw4_arena *arena;dw4_handle record;} dw4_property_ref;
dw4_property_ref dw4_property_reference(const dw4_property_folder *,const char *,dw4_property_type);
/* Retain the actual typed list/folder for a recovered reference field. Release
 * through list_release (which owns the recursive payload), never arena_free.
 * Refresh from the current folder after publication; the old retained list
 * remains valid through replacement and owner teardown. No concurrent mutation. */
dw4_handle dw4_property_list_acquire(const dw4_property_folder *,const char *,dw4_property_type);
dw4_handle dw4_property_folder_acquire(const dw4_property_folder *);
void dw4_property_list_release(dw4_arena *,dw4_handle);
/* Query without exposing an internal property pointer that record publication
 * could expire. Scalars have count one; lists report their actual count. */
int dw4_property_describe(const dw4_property_folder *,const char *,dw4_property_type *,size_t *);
/* String arrays preserve empty sockets as NULL and copy non-null entries. */
int dw4_property_set_strings(dw4_property_folder *,const char *,const char *const *,size_t);
const char *dw4_property_string_at(const dw4_property_folder *,const char *,size_t);
/* Owned beUnicodeObj array payloads (retail property type 6). NULL entries
 * differ from present empty objects; code counts exclude any terminator. */
typedef struct {const uint16_t *codes;size_t count;int present;} dw4_unicode_object;
int dw4_property_set_unicode_objects(dw4_property_folder *,const char *,const dw4_unicode_object *,size_t);
int dw4_property_unicode_object(const dw4_property_folder *,const char *,size_t,dw4_unicode_object *);
dw4_property_folder *dw4_property_child(dw4_property_folder *,const char *,int create);
/* SYSisJoinPlayer/name/level/digimon/weapon read these records; returns 1 for an
 * unrelated method, 0 on success, -1 for missing records/invalid arguments. */
/* GAMERAM GETCOMMON/GETPLAYER[1..4] typed return; owner outlives Lua references. */
int dw4_playerrecords_service(void *,const char *,const dw4_script_value *,size_t,dw4_script_value *,char *,size_t);
int dw4_playerrecords_call(void *,const char *,const dw4_script_value *,size_t,
    dw4_script_value *,char *,size_t);
/* Native item payload for beNDMWItem* object arrays; values follow recovered
 * _kindNo/_recNo/_isEquip/_revision/_pocket, without guest pointers. */
typedef struct {int32_t kind,record,equipped,revision,pocket;} dw4_item_record;
/* Item-list ownership outside a property folder (e.g. SUBWND stock). Release
 * the owned result through property_list_release; views expire on mutation. */
dw4_handle dw4_item_list_new(dw4_arena *,const dw4_item_record *,size_t);
const dw4_item_record *dw4_item_list_view(dw4_arena *,dw4_handle,size_t *);
int dw4_item_list_set(dw4_arena *,dw4_handle,size_t,const dw4_item_record *);
int dw4_property_set_items(dw4_property_folder *,const char *,const dw4_item_record *,size_t);
const dw4_item_record *dw4_property_items(const dw4_property_folder *,const char *,size_t *);
int dw4_property_item_count(const dw4_property_folder *,const char *,size_t *);
/* Move a successfully staged slot into the session, preserving folder address.
 * Updates NINZU; staged owner receives the old slot for disposal. */
/* Keep ISUSE and common NINZU consistent when login preparation fails. */
int dw4_playerrecords_join(dw4_playerrecords *,int32_t,int);
int dw4_playerrecords_publish(dw4_playerrecords *,dw4_playerrecords *,int32_t);
/* Copy non-folder values into a private staging folder. Commit swaps payloads
 * after complete type/allocation preflight; existing child addresses survive.
 * The staging folder receives old values and must subsequently be destroyed. */
int dw4_property_copy_values(dw4_property_folder *,const dw4_property_folder *);
int dw4_property_commit_values(dw4_property_folder *,dw4_property_folder *);
/* Preflight and reserve both destination tables before moving either payload.
 * Used by accepted local-co-op transfers; destinations must be disjoint. */
int dw4_property_commit_pair(dw4_property_folder *,dw4_property_folder *,
    dw4_property_folder *,dw4_property_folder *);
/* A name code as one display character: ASCII as is, the full-width forms (U+FF01..U+FF5E) the game's name grid stores as their ASCII twin,
 * anything else '?'. */
static inline char dw4_name_char(uint16_t code){return code<128?(char)code:code>=0xFF01&&code<=0xFF5E?(char)(code-0xFF00+0x20):'?';}
#endif
