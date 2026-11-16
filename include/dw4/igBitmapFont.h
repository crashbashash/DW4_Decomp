#ifndef DW4_IGBITMAPFONT_H
#define DW4_IGBITMAPFONT_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igBitmapFont_metaObject;
void igBitmapFont_RunStaticInit(void);
struct CallbackArray *igBitmapFont_Register(void);

#ifdef __cplusplus
}
#endif

#endif
