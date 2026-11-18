#ifndef DW4_IGGEOMETRYATTR_H
#define DW4_IGGEOMETRYATTR_H

struct igGeometryAttr;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igGeometryAttr_metaObject;
struct igGeometryAttr *igGeometryAttr_Create(int allocator);

void igGeometryAttr_EnsureRegistered(void);
struct igMetaObject *igGeometryAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
