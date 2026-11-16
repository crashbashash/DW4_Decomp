#ifndef DW4_BEMETERCTRL_H
#define DW4_BEMETERCTRL_H

struct beMeterCtrl;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beMeterCtrl *beMeterCtrl_CreateInstance(int allocator);
struct igMetaEnum *beMeterCtrl_GetMsgActionEnum(void);

extern struct igMetaObject *g_beMeterCtrl_metaObject;

#ifdef __cplusplus
}
#endif

#endif
