#ifndef DW4_BESTATICINFOCTL_H
#define DW4_BESTATICINFOCTL_H

struct beStaticInfoCtl;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beStaticInfoCtl *beStaticInfoCtl_CreateInstance(int allocator);
struct igMetaEnum *beStaticInfoCtl_GetMessageEnum(void);

extern struct igMetaObject *g_beStaticInfoCtl_metaObject;

#ifdef __cplusplus
}
#endif

#endif
