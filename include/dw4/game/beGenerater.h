#ifndef DW4_BEGENERATER_H
#define DW4_BEGENERATER_H

struct beGenerater;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beGenerater *beGenerater_CreateInstance(int allocator);
struct igMetaEnum *beGenerater_GetMsgActionEnum(void);

extern struct igMetaObject *g_beGenerater_metaObject;

#ifdef __cplusplus
}
#endif

#endif
