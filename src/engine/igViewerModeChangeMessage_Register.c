/* 0x0045a590 igViewerModeChangeMessage_Register: registers class igViewerModeChangeMessage with the object system, derived from igMessage.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMessage_GetPublishedMetaObject[];
extern char igMessage_Register[];
extern char igViewerModeChangeMessage_GetVTable[];
extern char thunk_igViewerModeChangeMessage_GetMetaObject[];
extern char igViewerModeChangeMessage_className[];
extern char g_igViewerModeChangeMessage_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igViewerModeChangeMessage_InitFields();

void igViewerModeChangeMessage_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewerModeChangeMessage_metaObject, /* published MetaObject slot */
        igMessage_Register,                              /* base class registrar */
        igMessage_GetPublishedMetaObject,       /* base class MetaObject accessor */
        thunk_igViewerModeChangeMessage_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igViewerModeChangeMessage_className,  /* class name */
        0x10,                                            /* instance size */
        igViewerModeChangeMessage_GetVTable,             /* vtable getter */
        &igViewerModeChangeMessage_InitFields,           /* field adder */
        0,                                               /* extra callback item */
        0                                                /* callback list */
    );
}
