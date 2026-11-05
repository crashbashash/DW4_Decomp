/* 0x00238ee0 igSearchSceneGraph_Register: registers class igSearchSceneGraph with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject_0014a6e0[];
extern char igSearchSceneGraph_GetVTable[];
extern char thunk_igSearchSceneGraph_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igSearchSceneGraph_callbackList_00498290[];
extern char s_igSearchSceneGraph_className_004e9d40[];
extern char g_igSearchSceneGraph_metaObject_0056dc60[];
int GpFlag_SetOnce_00238d50();
int igMetaObject_RegisterClass();
int igSearchSceneGraph_InitFields();

void igSearchSceneGraph_Register(void) {
    GpFlag_SetOnce_00238d50();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSearchSceneGraph_metaObject_0056dc60,      /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject_0014a6e0, /* base class MetaObject accessor */
        thunk_igSearchSceneGraph_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igSearchSceneGraph_className_004e9d40,       /* class name */
        0x1C,                                          /* instance size */
        igSearchSceneGraph_GetVTable,                  /* vtable getter */
        &igSearchSceneGraph_InitFields,                /* field adder */
        0,                                             /* extra callback item */
        g_igSearchSceneGraph_callbackList_00498290     /* callback list */
    );
}
