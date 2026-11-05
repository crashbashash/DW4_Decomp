/* 0x002290d0 igFileInfo_Register: registers class igFileInfo with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject_0014a6e0[];
extern char igFileInfo_GetVTable[];
extern char thunk_igFileInfo_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igFileInfo_callbackList_00497f10[];
extern char s_igFileInfo_className_004e7e38[];
extern char g_igFileInfo_metaObject_0056da38[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();
int igFileInfo_InitFields();

void igFileInfo_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFileInfo_metaObject_0056da38,              /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject_0014a6e0, /* base class MetaObject accessor */
        thunk_igFileInfo_GetMetaObject,                /* own MetaObject accessor (stored at +0x54) */
        s_igFileInfo_className_004e7e38,               /* class name */
        0x1C,                                          /* instance size */
        igFileInfo_GetVTable,                          /* vtable getter */
        &igFileInfo_InitFields,                        /* field adder */
        0,                                             /* extra callback item */
        g_igFileInfo_callbackList_00497f10             /* callback list */
    );
}
