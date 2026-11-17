#ifndef DW4_IGGEOMETRYATTRLIST_H
#define DW4_IGGEOMETRYATTRLIST_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igGeometryAttrList_EnsureRegistered(void);
struct igMetaObject *igGeometryAttrList_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
