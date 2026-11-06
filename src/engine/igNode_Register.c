/* 0x0019cf20 igNode_Register: registers class igNode with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject[];
extern char igNode_GetVTable[];
extern char thunk_igNode_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igNode_callbackList[];
extern char igNode_className[];
extern char g_igNode_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igNode_InitFields();

void igNode_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNode_metaObject,                  /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igNode_GetMetaObject,                    /* own MetaObject accessor (stored at +0x54) */
        igNode_className,                   /* class name */
        0x1C,                                          /* instance size */
        igNode_GetVTable,                              /* vtable getter */
        &igNode_InitFields,                            /* field adder */
        0,                                             /* extra callback item */
        g_igNode_callbackList                 /* callback list */
    );
}
