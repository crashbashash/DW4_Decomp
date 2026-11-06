/* 0x004508a0 igFont_Register: registers class igFont with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject[];
int igNamedObject_Register();
int thunk_igFont_GetMetaObject();
extern char g_igFont_callbackList[];
extern char igFont_className[];
extern char g_igFont_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igFont_InitFields();

void igFont_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        1,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFont_metaObject,                  /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igFont_GetMetaObject,                    /* own MetaObject accessor (stored at +0x54) */
        igFont_className,                   /* class name */
        0x1C,                                          /* instance size */
        0,                                             /* vtable getter */
        &igFont_InitFields,                            /* field adder */
        0,                                             /* extra callback item */
        g_igFont_callbackList                 /* callback list */
    );
}
