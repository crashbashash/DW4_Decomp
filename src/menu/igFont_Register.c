/* 0x004508a0 igFont_Register: registers class igFont with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject_0014a6e0[];
int igNamedObject_Register();
int thunk_igFont_GetMetaObject();
extern char g_igFont_callbackList_004d0670[];
extern char s_igFont_className_0051e4a0[];
extern char g_igFont_metaObject_0058c510[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igFont_InitFields();

void igFont_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        1,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFont_metaObject_0058c510,                  /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject_0014a6e0, /* base class MetaObject accessor */
        thunk_igFont_GetMetaObject,                    /* own MetaObject accessor (stored at +0x54) */
        s_igFont_className_0051e4a0,                   /* class name */
        0x1C,                                          /* instance size */
        0,                                             /* vtable getter */
        &igFont_InitFields,                            /* field adder */
        0,                                             /* extra callback item */
        g_igFont_callbackList_004d0670                 /* callback list */
    );
}
