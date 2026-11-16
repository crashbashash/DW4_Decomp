#ifndef DW4_BETEXTURECTRL_H
#define DW4_BETEXTURECTRL_H

struct beTextureCtrl;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beTextureCtrl *beTextureCtrl_CreateInstance(int allocator);

extern struct igMetaObject *g_beTextureCtrl_metaObject;

#ifdef __cplusplus
}
#endif

#endif
