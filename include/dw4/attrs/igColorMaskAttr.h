#ifndef DW4_IGCOLORMASKATTR_H
#define DW4_IGCOLORMASKATTR_H

struct igColorMaskAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igColorMaskAttr *igColorMaskAttr_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
