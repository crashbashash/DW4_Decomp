#ifndef DW4_IGCOLORATTR_H
#define DW4_IGCOLORATTR_H

struct igColorAttr;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igColorAttr_metaObject;
struct igColorAttr *igColorAttr_CreateInstance(int allocator);
struct igMetaObject *igColorAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
