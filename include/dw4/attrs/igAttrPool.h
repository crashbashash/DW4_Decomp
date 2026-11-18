#ifndef DW4_IGATTRPOOL_H
#define DW4_IGATTRPOOL_H

struct igAttrPool;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igAttrPool *igAttrPool_Create(struct igMemoryPoolView *pool);
struct igAttrPool *igAttrPool_GetStaticAttrPool(void);
void igAttrPool_UserUnregister(void);
int igAttrPool_AddNonSharableType(int *p, void *meta);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "dw4/core/igSmartPointer.h"
struct igObject;
extern "C" igSmartPointer<igObject> igAttrPool_GetSharedAttr(igAttrPool *pool, igSmartPointer<igObject> attr);
#endif

#endif
