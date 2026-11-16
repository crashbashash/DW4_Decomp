#ifndef DW4_IGINSIGHTCORE_H
#define DW4_IGINSIGHTCORE_H

struct igInsightCore;
struct igMetaObject;
struct igObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igInsightCore *igInsightCore_CreateInstance(int allocator);
struct igMetaObject *igInsightCore_GetOrCreateMetaObject(void);
void igInsightCore_EnsureRegistered(void);

void igInsightCore_AddManager(struct igInsightCore *core, struct igObject *manager);
void igInsightCore_RemoveManager(struct igInsightCore *core, struct igObject *manager);
/* The core's manager whose meta object is `kind`, or null. */
struct igObject *igInsightCore_FindManager(struct igInsightCore *core, struct igMetaObject *kind);
void igInsightCore_AddToScheduler(struct igInsightCore *core, struct igObject *object);
void igInsightCore_RemoveFromScheduler(struct igInsightCore *core, struct igObject *object);
void igInsightCore_AddRenderer(struct igInsightCore *core, struct igObject *renderer);
void igInsightCore_RemoveRenderer(struct igInsightCore *core, struct igObject *renderer);
/* Makes `second` draw after `first`. */
void igInsightCore_AddRendererOrder(struct igInsightCore *core, struct igObject *first, struct igObject *second);
void igInsightCore_AddInfo(struct igInsightCore *core, struct igObject *info);

#ifdef __cplusplus
}
#endif

#endif
