#ifndef DW4_BECOPYTRANSFORM_H
#define DW4_BECOPYTRANSFORM_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *beCopyTransform_GetMetaObject(void);
void beCopyTransform_RegisterTraversal(void);

#ifdef __cplusplus
}
#endif

#endif
