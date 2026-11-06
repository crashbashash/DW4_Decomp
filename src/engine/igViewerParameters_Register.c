/* 0x0045b5a0 igViewerParameters_Register: registers class igViewerParameters with the object system, derived from igModel.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igModel_GetPublishedMetaObject[];
extern char igModel_Register[];
extern char igViewerParameters_GetVTable[];
extern char thunk_igViewerParameters_GetMetaObject[];
extern char g_igViewerParameters_callbackList[];
extern char igViewerParameters_className[];
extern char g_igViewerParameters_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igViewerParameters_InitFields();

void igViewerParameters_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewerParameters_metaObject, /* published MetaObject slot */
        igModel_Register,                         /* base class registrar */
        igModel_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igViewerParameters_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igViewerParameters_className,  /* class name */
        0x108,                                    /* instance size */
        igViewerParameters_GetVTable,             /* vtable getter */
        &igViewerParameters_InitFields,           /* field adder */
        0,                                        /* extra callback item */
        g_igViewerParameters_callbackList  /* callback list */
    );
}
