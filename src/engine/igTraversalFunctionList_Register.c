/* 0x0019a810 igTraversalFunctionList_Register: registers class igTraversalFunctionList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igTraversalFunctionList_GetVTable[];
extern char thunk_igTraversalFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char igTraversalFunctionList_className[];
extern char g_igTraversalFunctionList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igTraversalFunctionList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTraversalFunctionList_metaObject, /* published MetaObject slot */
        igDataList_Register,                           /* base class registrar */
        igDataList_GetPublishedMetaObject,             /* base class MetaObject accessor */
        thunk_igTraversalFunctionList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igTraversalFunctionList_className,  /* class name */
        0x14,                                          /* instance size */
        igTraversalFunctionList_GetVTable,             /* vtable getter */
        0,                                             /* field adder */
        0,                                             /* extra callback item */
        0                                              /* callback list */
    );
}
