#ifndef DW4_IGDEPTHSTATEATTR_H
#define DW4_IGDEPTHSTATEATTR_H

struct igDepthStateAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igDepthStateAttr *igDepthStateAttr_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
