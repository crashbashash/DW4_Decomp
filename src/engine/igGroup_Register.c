/* 0x0019f340 igGroup_Register: registers class igGroup with the object system, derived from igNode.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNode_Register[];
extern char igNode_GetPublishedMetaObject[];
extern char igGroup_GetVTable[];
extern char thunk_igGroup_GetMetaObject[];
extern char g_igGroup_callbackList[];
extern char igGroup_className[];
extern char g_igGroup_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igGroup_InitFields();

void igGroup_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGroup_metaObject,          /* published MetaObject slot */
        igNode_Register,                        /* base class registrar */
        igNode_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igGroup_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        igGroup_className,           /* class name */
        0x20,                                   /* instance size */
        igGroup_GetVTable,                      /* vtable getter */
        &igGroup_InitFields,                    /* field adder */
        0,                                      /* extra callback item */
        g_igGroup_callbackList         /* callback list */
    );
}
