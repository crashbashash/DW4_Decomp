#ifndef DW4_BESAVEUTIL_H
#define DW4_BESAVEUTIL_H

struct beSaveUtil;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beSaveUtil *beSaveUtil_CreateInstance(int allocator);
struct igMetaEnum *beSaveUtil_GetMessageEnum(void);

extern struct igMetaObject *g_beSaveUtil_metaObject;

#ifdef __cplusplus
}
#endif

#endif
