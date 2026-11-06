/* 0x0045bc20 igViewerGuiFactory_Register: registers class igViewerGuiFactory with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igViewerGuiFactory_GetVTable[];
extern char thunk_igViewerGuiFactory_GetMetaObject[];
extern char g_igViewerGuiFactory_callbackList[];
extern char igViewerGuiFactory_className[];
extern char g_igViewerGuiFactory_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igViewerGuiFactory_InitFields();

void igViewerGuiFactory_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewerGuiFactory_metaObject, /* published MetaObject slot */
        igObject_Register,                        /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,    /* base class MetaObject accessor */
        thunk_igViewerGuiFactory_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igViewerGuiFactory_className,  /* class name */
        0x28,                                     /* instance size */
        igViewerGuiFactory_GetVTable,             /* vtable getter */
        &igViewerGuiFactory_InitFields,           /* field adder */
        0,                                        /* extra callback item */
        g_igViewerGuiFactory_callbackList  /* callback list */
    );
}
