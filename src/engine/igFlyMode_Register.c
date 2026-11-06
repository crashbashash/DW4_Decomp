/* 0x0045ca30 igFlyMode_Register: registers class igFlyMode with the object system, derived from igViewMode.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igViewMode_GetPublishedMetaObject[];
extern char igFlyMode_GetVTable[];
extern char thunk_igFlyMode_GetMetaObject[];
extern char igViewMode_Register[];
extern char g_igFlyMode_callbackList[];
extern char igFlyMode_className[];
extern char g_igFlyMode_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igFlyMode_InitFields();

void igFlyMode_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFlyMode_metaObject,            /* published MetaObject slot */
        igViewMode_Register,                        /* base class registrar */
        igViewMode_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igFlyMode_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        igFlyMode_className,             /* class name */
        0xA0,                                       /* instance size */
        igFlyMode_GetVTable,                        /* vtable getter */
        &igFlyMode_InitFields,                      /* field adder */
        0,                                          /* extra callback item */
        g_igFlyMode_callbackList           /* callback list */
    );
}
