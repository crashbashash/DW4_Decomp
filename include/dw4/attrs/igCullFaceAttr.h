#ifndef DW4_IGCULLFACEATTR_H
#define DW4_IGCULLFACEATTR_H

struct igCullFaceAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igCullFaceAttr *igCullFaceAttr_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
