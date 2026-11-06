/* 0x0045a7b0 igViewerLoadingFileMessage_Register: registers class igViewerLoadingFileMessage with the object system, derived from igMessage.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMessage_GetPublishedMetaObject[];
extern char igMessage_Register[];
extern char igViewerLoadingFileMessage_GetVTable[];
extern char thunk_igViewerLoadingFileMessage_GetMetaObject[];
extern char igViewerLoadingFileMessage_className[];
extern char g_igViewerLoadingFileMessage_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igViewerLoadingFileMessage_InitFields();

void igViewerLoadingFileMessage_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                                /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewerLoadingFileMessage_metaObject, /* published MetaObject slot */
        igMessage_Register,                               /* base class registrar */
        igMessage_GetPublishedMetaObject,        /* base class MetaObject accessor */
        thunk_igViewerLoadingFileMessage_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igViewerLoadingFileMessage_className,  /* class name */
        0x10,                                             /* instance size */
        igViewerLoadingFileMessage_GetVTable,             /* vtable getter */
        &igViewerLoadingFileMessage_InitFields,           /* field adder */
        0,                                                /* extra callback item */
        0                                                 /* callback list */
    );
}
