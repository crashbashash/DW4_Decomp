/* 0x0019dce0 igLightSet_Register: registers class igLightSet with the object system, derived from igNode.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNode_Register[];
extern char igLightSet_GetVTable[];
extern char thunk_igLightSet_GetMetaObject[];
extern char igNode_GetPublishedMetaObject[];
extern char g_igLightSet_callbackList[];
extern char igLightSet_className[];
extern char g_igLightSet_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igLightSet_InitFields();

void igLightSet_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLightSet_metaObject,       /* published MetaObject slot */
        igNode_Register,                        /* base class registrar */
        igNode_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igLightSet_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igLightSet_className,        /* class name */
        0x20,                                   /* instance size */
        igLightSet_GetVTable,                   /* vtable getter */
        &igLightSet_InitFields,                 /* field adder */
        0,                                      /* extra callback item */
        g_igLightSet_callbackList      /* callback list */
    );
}
