#ifndef DW4_IGGEOMETRYMASKATTR_H
#define DW4_IGGEOMETRYMASKATTR_H

struct igGeometryMaskAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igGeometryMaskAttr *igGeometryMaskAttr_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
