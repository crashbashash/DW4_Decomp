#ifndef DW4_IGRENDERDESTINATIONATTR_H
#define DW4_IGRENDERDESTINATIONATTR_H

struct igRenderDestinationAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igRenderDestinationAttr *igRenderDestinationAttr_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
