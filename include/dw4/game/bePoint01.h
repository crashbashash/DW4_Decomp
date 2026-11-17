#ifndef DW4_BEPOINT01_H
#define DW4_BEPOINT01_H

struct bePoint01;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct bePoint01 *bePoint01_CreateInstance(int allocator);
struct igMetaEnum *bePoint01_GetMsgActionEnum(void);

extern struct igMetaObject *g_bePoint01_metaObject;

#ifdef __cplusplus
}
#endif

#endif
