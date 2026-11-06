/* 0x0045c340 igPickMode_Register: registers class igPickMode with the object system, derived from igViewMode.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igViewMode_GetPublishedMetaObject[];
extern char igPickMode_GetVTable[];
extern char thunk_igPickMode_GetMetaObject[];
extern char igViewMode_Register[];
extern char g_igPickMode_callbackList[];
extern char igPickMode_className[];
extern char g_igPickMode_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igPickMode_InitFields();

void igPickMode_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPickMode_metaObject,           /* published MetaObject slot */
        igViewMode_Register,                        /* base class registrar */
        igViewMode_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPickMode_GetMetaObject,             /* own MetaObject accessor (stored at +0x54) */
        igPickMode_className,            /* class name */
        0xBC,                                       /* instance size */
        igPickMode_GetVTable,                       /* vtable getter */
        &igPickMode_InitFields,                     /* field adder */
        0,                                          /* extra callback item */
        g_igPickMode_callbackList          /* callback list */
    );
}
