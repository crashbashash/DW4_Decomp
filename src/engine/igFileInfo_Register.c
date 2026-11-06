/* 0x002290d0 igFileInfo_Register: registers class igFileInfo with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject[];
extern char igFileInfo_GetVTable[];
extern char thunk_igFileInfo_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igFileInfo_callbackList[];
extern char igFileInfo_className[];
extern char g_igFileInfo_metaObject[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();
int igFileInfo_InitFields();

void igFileInfo_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFileInfo_metaObject,              /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igFileInfo_GetMetaObject,                /* own MetaObject accessor (stored at +0x54) */
        igFileInfo_className,               /* class name */
        0x1C,                                          /* instance size */
        igFileInfo_GetVTable,                          /* vtable getter */
        &igFileInfo_InitFields,                        /* field adder */
        0,                                             /* extra callback item */
        g_igFileInfo_callbackList             /* callback list */
    );
}
