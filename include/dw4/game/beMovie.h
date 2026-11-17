#ifndef DW4_BEMOVIE_H
#define DW4_BEMOVIE_H

struct beMovie;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beMovie *beMovie_CreateInstance(int allocator);
struct igMetaEnum *beMovie_GetMessageEnum(void);

extern struct igMetaObject *g_beMovie_metaObject;

#ifdef __cplusplus
}
#endif

#endif
