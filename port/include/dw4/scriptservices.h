/* Native receiver registry and retail-timed SD message queue. */
#ifndef DW4_SCRIPTSERVICES_H
#define DW4_SCRIPTSERVICES_H
#include "dw4/script.h"
typedef struct dw4_scriptservices dw4_scriptservices;
dw4_scriptservices *dw4_scriptservices_open(void);
/* A retail manager exists even when this scene owns no matching RAM rows.
 * Declare that category without installing a synthetic receiver. */
int dw4_scriptservices_category(dw4_scriptservices *,const char *);
void dw4_scriptservices_close(dw4_scriptservices *);
/* Scene boundary: clear every receiver, category and timed message, including
 * failure/selector state. Preserve clock and monotonic tokens. Busy calls are
 * rejected before mutation; borrowed receiver owners may release afterward. */
int dw4_scriptservices_busy(const dw4_scriptservices *);
int dw4_scriptservices_remove_all(dw4_scriptservices *);
/* Host tokens and callbacks never occupy recovered four-byte references.
 * Registration copies category/name. Nil on either side matches every name;
 * selector or receiver id -1 is a wildcard; -2 selects the first inactive
 * receiver. Callbacks receive the typed selector, key and optional value;
 * the queue consumes the delay argument before calling the receiver.
 * Optional encoded values remain strings for the owning service to decode. */
uint64_t dw4_scriptservices_register(dw4_scriptservices *, uint64_t scope,
    const char *category, const char *name, int32_t id, int active,
    dw4_script_binding handler, void *user);
void dw4_scriptservices_unregister(dw4_scriptservices *, uint64_t token);
/* Receivers registered under category/name (name NULL = any) and how many of them are active. */
size_t dw4_scriptservices_count(const dw4_scriptservices *,const char *category,const char *name,size_t *active);
int32_t dw4_scriptservices_first_inactive(const dw4_scriptservices *,const char *category,const char *name);
int dw4_scriptservices_is_active(const dw4_scriptservices *,const char *category,const char *name,int32_t id);
void dw4_scriptservices_active(dw4_scriptservices *, uint64_t token, int active);
/* Cancel messages owned by a scope; remove_scope also unregisters receivers.
 * Call before releasing borrowed service state on unload or retry. */
void dw4_scriptservices_cancel(dw4_scriptservices *, uint64_t scope);
void dw4_scriptservices_remove_scope(dw4_scriptservices *, uint64_t scope);
/* Scope of subsequently queued messages; zero is a valid session scope.
 * Timed callbacks inherit their message's publication scope and restore this
 * ambient scope on return. Explicit changes inside a callback are local to it. */
void dw4_scriptservices_scope(dw4_scriptservices *, uint64_t scope);
/* dw4_script_binding entry point. sd accepts canonical 4/5/6 argument calls
 * and the retail 5-argument numeric-delay overload. querySD is immediate.
 * Unknown categories fail; missing receivers in registered categories return
 * nil. Ordinary sd returns no Lua value. Reentrant immediate calls are safe. */
int dw4_scriptservices_call(void *, const char *, const dw4_script_value *,
    size_t, dw4_script_value *, char *, size_t);
/* MDLisLive (373dd0) ORs every numeric ISRUN result, unlike querySD's first
 * result. Missing rows return numeric zero; callbacks retain normal lifetimes. */
int dw4_scriptservices_any(dw4_scriptservices *,const dw4_script_value *,size_t,
    dw4_script_value *,char *,size_t);
/* Advance once after world-clock sampling, before DM. Delay units are retail
 * integer frames * 16666666 ns, with signed 64-bit wrapping arithmetic.
 * Equal deadlines retain publication order. No tick means no expiry during holds.
 * A failed callback latches the service; recreate it to retry. */
int dw4_scriptservices_tick(dw4_scriptservices *, uint64_t world_ns);
size_t dw4_scriptservices_pending(const dw4_scriptservices *);
const char *dw4_scriptservices_error(const dw4_scriptservices *);
#endif
