/* 0x00452630 igBitmapFont_Register: registers class igBitmapFont with the object system, derived from igFont.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igFont_Register[];
extern char igBitmapFont_GetVTable[];
extern char thunk_igBitmapFont_GetMetaObject[];
extern char igFont_GetPublishedMetaObject_004526c0[];
extern char g_igBitmapFont_callbackList_004d0860[];
extern char s_igBitmapFont_className_0051e740[];
extern char g_igBitmapFont_metaObject_0058c620[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igBitmapFont_InitFields();

void igBitmapFont_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBitmapFont_metaObject_0058c620,     /* published MetaObject slot */
        igFont_Register,                        /* base class registrar */
        igFont_GetPublishedMetaObject_004526c0, /* base class MetaObject accessor */
        thunk_igBitmapFont_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igBitmapFont_className_0051e740,      /* class name */
        0x24,                                   /* instance size */
        igBitmapFont_GetVTable,                 /* vtable getter */
        &igBitmapFont_InitFields,               /* field adder */
        0,                                      /* extra callback item */
        g_igBitmapFont_callbackList_004d0860    /* callback list */
    );
}
