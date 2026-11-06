/* 0x00233390 igViewportResizedMessage_Register: registers class igViewportResizedMessage with the object system, derived from igMessage.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMessage_GetPublishedMetaObject[];
extern char igMessage_Register[];
extern char igViewportResizedMessage_GetVTable[];
extern char thunk_igViewportResizedMessage_GetMetaObject[];
extern char igViewportResizedMessage_className[];
extern char g_igViewportResizedMessage_metaObject[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();
int igViewportResizedMessage_InitFields();

void igViewportResizedMessage_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewportResizedMessage_metaObject, /* published MetaObject slot */
        igMessage_Register,                             /* base class registrar */
        igMessage_GetPublishedMetaObject,      /* base class MetaObject accessor */
        thunk_igViewportResizedMessage_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igViewportResizedMessage_className,  /* class name */
        0x18,                                           /* instance size */
        igViewportResizedMessage_GetVTable,             /* vtable getter */
        &igViewportResizedMessage_InitFields,           /* field adder */
        0,                                              /* extra callback item */
        0                                               /* callback list */
    );
}
