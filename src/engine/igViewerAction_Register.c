/* 0x004591a0 igViewerAction_Register: registers class igViewerAction with the object system, derived from igAction.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igAction_GetPublishedMetaObject[];
extern char igAction_Register[];
extern char igViewerAction_GetVTable[];
extern char thunk_igViewerAction_GetMetaObject[];
extern char g_igViewerAction_callbackList[];
extern char igViewerAction_className[];
extern char g_igViewerAction_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igViewerAction_InitFields();

void igViewerAction_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewerAction_metaObject,     /* published MetaObject slot */
        igAction_Register,                        /* base class registrar */
        igAction_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igViewerAction_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igViewerAction_className,      /* class name */
        0x18,                                     /* instance size */
        igViewerAction_GetVTable,                 /* vtable getter */
        &igViewerAction_InitFields,               /* field adder */
        0,                                        /* extra callback item */
        g_igViewerAction_callbackList    /* callback list */
    );
}
