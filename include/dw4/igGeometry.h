#ifndef DW4_IGGEOMETRY_H
#define DW4_IGGEOMETRY_H

struct igGeometry;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igGeometry *igGeometry_CreateInstance(int allocator);
struct igMetaObject *igGeometry_GetOrCreateMetaObject(void);
void igGeometry_Register(void);

#ifdef __cplusplus
}
#endif

#endif
