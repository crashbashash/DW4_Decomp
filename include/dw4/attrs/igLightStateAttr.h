#ifndef DW4_IGLIGHTSTATEATTR_H
#define DW4_IGLIGHTSTATEATTR_H

struct igMetaObject;
struct igLightStateAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igLightStateAttr_metaObject;
struct igMetaObject *igLightStateAttr_GetMetaObject(void);
struct igLightStateAttr *igLightStateAttr_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
