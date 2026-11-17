#ifndef DW4_BESELECTCTRL_H
#define DW4_BESELECTCTRL_H

struct beSelectCtrl;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beSelectCtrl *beSelectCtrl_CreateInstance(int allocator);
struct igMetaEnum *beSelectCtrl_GetMessageEnum(void);

extern struct igMetaObject *g_beSelectCtrl_metaObject;

#ifdef __cplusplus
}
#endif

#endif
