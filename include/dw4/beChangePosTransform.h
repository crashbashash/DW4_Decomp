#ifndef DW4_BECHANGEPOSTRANSFORM_H
#define DW4_BECHANGEPOSTRANSFORM_H

struct beChangePosTransform;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beChangePosTransform *beChangePosTransform_CreateInstance(int allocator);

extern struct igMetaObject *g_beChangePosTransform_metaObject;

#ifdef __cplusplus
}
#endif

#endif
