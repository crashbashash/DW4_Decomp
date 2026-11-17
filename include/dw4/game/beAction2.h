#ifndef DW4_BEACTION2_H
#define DW4_BEACTION2_H

struct beAction2;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beAction2 *beAction2_CreateInstance(int allocator);
struct igMetaEnum *beAction2_GetMessageEnum(void);

extern struct igMetaObject *g_beAction2_metaObject;

#ifdef __cplusplus
}
#endif

#endif
