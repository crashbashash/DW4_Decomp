#ifndef DW4_BESOUND_H
#define DW4_BESOUND_H

struct beSound;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beSound *beSound_CreateInstance(int allocator);
struct igMetaEnum *beSound_GetMessageEnum(void);

extern struct igMetaObject *g_beSound_metaObject;

#ifdef __cplusplus
}
#endif

#endif
