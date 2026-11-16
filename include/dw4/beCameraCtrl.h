#ifndef DW4_BECAMERACTRL_H
#define DW4_BECAMERACTRL_H

struct beCameraCtrl;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beCameraCtrl *beCameraCtrl_CreateInstance(int allocator);
struct igMetaEnum *beCameraCtrl_GetMessageEnum(void);

extern struct igMetaObject *g_beCameraCtrl_metaObject;

#ifdef __cplusplus
}
#endif

#endif
