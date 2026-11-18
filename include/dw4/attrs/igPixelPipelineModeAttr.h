#ifndef DW4_IGPIXELPIPELINEMODEATTR_H
#define DW4_IGPIXELPIPELINEMODEATTR_H

struct igPixelPipelineModeAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igPixelPipelineModeAttr *igPixelPipelineModeAttr_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
