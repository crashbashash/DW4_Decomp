#ifndef DW4_IGFONT_H
#define DW4_IGFONT_H

struct igFont;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igFont *igFont_Destroy(struct igFont *self, short delete_storage);

extern struct igMetaObject *g_igFont_metaObject;

#ifdef __cplusplus
}
#endif

#endif
