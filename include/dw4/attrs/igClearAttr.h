#ifndef DW4_IGCLEARATTR_H
#define DW4_IGCLEARATTR_H

struct igMetaObject;
struct igClearAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igClearAttr_metaObject;
struct igMetaObject *igClearAttr_GetMetaObject(void);
struct igClearAttr *igClearAttr_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
