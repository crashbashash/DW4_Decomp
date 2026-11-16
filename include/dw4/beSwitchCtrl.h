#ifndef DW4_BESWITCHCTRL_H
#define DW4_BESWITCHCTRL_H

struct beSwitchCtrl;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beSwitchCtrl *beSwitchCtrl_CreateInstance(int allocator);
struct igMetaEnum *beSwitchCtrl_GetMessageEnum(void);

extern struct igMetaObject *g_beSwitchCtrl_metaObject;

#ifdef __cplusplus
}
#endif

#endif
