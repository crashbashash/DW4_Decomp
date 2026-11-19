#ifndef DW4_IGFRUSTCULLTRAVERSAL_H
#define DW4_IGFRUSTCULLTRAVERSAL_H

struct igFrustCullTraversal;
struct igMemoryPoolView;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igCommonTraversal_metaObject;
int igFrustCullTraversal_ClassifyBox(const float *boxMin, const float *boxMax, const float *matrix);
struct igFrustCullTraversal *FUN_0019fde0(struct igMemoryPoolView *pool);
/* Sets the outer frustum-cull scale when it is at least 1 and below the outer scissor-window scale;
 * returns whether it was set. */
int FUN_001c5160(struct igFrustCullTraversal *self, float scale);

#ifdef __cplusplus
}
#endif

#endif
