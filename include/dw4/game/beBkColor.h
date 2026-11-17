#ifndef DW4_BEBKCOLOR_H
#define DW4_BEBKCOLOR_H

struct beBkColor;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beBkColor *beBkColor_CreateInstance(int allocator);

extern struct igMetaObject *g_beBkColor_metaObject;

#ifdef __cplusplus
}
#endif

#endif
