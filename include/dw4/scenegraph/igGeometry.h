#ifndef DW4_IGGEOMETRY_H
#define DW4_IGGEOMETRY_H

struct CallbackArray;
struct igGeometry;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igGeometry *igGeometry_Destroy(struct igGeometry *self, short deleteFlag);
struct igMetaObject *igGeometry_GetPublishedMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
