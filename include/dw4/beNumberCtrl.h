#ifndef DW4_BENUMBERCTRL_H
#define DW4_BENUMBERCTRL_H

struct beNumberCtrl;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beNumberCtrl *beNumberCtrl_CreateInstance(int allocator);
struct igMetaEnum *beNumberCtrl_GetMessageEnum(void);

extern struct igMetaObject *g_beNumberCtrl_metaObject;

#ifdef __cplusplus
}
#endif

#endif
