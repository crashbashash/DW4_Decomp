#ifndef DW4_BEWATERPLAIN_H
#define DW4_BEWATERPLAIN_H

struct beWaterPlain;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beWaterPlain *beWaterPlain_CreateInstance(int allocator);
struct igMetaEnum *beWaterPlain_GetMessageEnum(void);

extern struct igMetaObject *g_beWaterPlain_metaObject;

#ifdef __cplusplus
}
#endif

#endif
