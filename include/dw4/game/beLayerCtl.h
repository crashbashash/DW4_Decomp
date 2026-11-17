#ifndef DW4_BELAYERCTL_H
#define DW4_BELAYERCTL_H

struct beLayerCtl;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beLayerCtl *beLayerCtl_CreateInstance(int allocator);
struct igMetaEnum *beLayerCtl_GetMessageEnum(void);
struct igMetaEnum *beLayerCtl_GetSwtCtlEnum(void);

extern struct igMetaObject *g_beLayerCtl_metaObject;

#ifdef __cplusplus
}
#endif

#endif
