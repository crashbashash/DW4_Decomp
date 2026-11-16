#ifndef DW4_IGFRUSTCULLTRAVERSAL_H
#define DW4_IGFRUSTCULLTRAVERSAL_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igCommonTraversal_metaObject;
int igFrustCullTraversal_ClassifyBox(const float *boxMin, const float *boxMax, const float *matrix);

#ifdef __cplusplus
}
#endif

#endif
