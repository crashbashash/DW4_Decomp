#ifndef DW4_IGBITMAPFONT_H
#define DW4_IGBITMAPFONT_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
extern int g_igBitmapFont_vtable[4];

extern struct igMetaObject *g_igBitmapFont_metaObject;
void igBitmapFont_RunStaticInit(void);
struct CallbackArray *igBitmapFont_Register(void);

#ifdef __cplusplus
}
#endif

#endif
