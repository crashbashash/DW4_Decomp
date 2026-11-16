#ifndef DW4_BELIGHTCTRL_H
#define DW4_BELIGHTCTRL_H

struct beLightCtrl;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beLightCtrl *beLightCtrl_CreateInstance(int allocator);
struct igMetaEnum *beLightCtrl_GetMsgActionEnum(void);

extern struct igMetaObject *g_beLightCtrl_metaObject;

#ifdef __cplusplus
}
#endif

#endif
