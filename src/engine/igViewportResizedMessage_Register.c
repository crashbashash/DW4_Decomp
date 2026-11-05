/* 0x00233390 igViewportResizedMessage_Register: registers class igViewportResizedMessage with the object system, derived from igMessage.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMessage_GetPublishedMetaObject_00231020[];
extern char igMessage_Register[];
extern char igViewportResizedMessage_GetVTable[];
extern char thunk_igViewportResizedMessage_GetMetaObject[];
extern char s_igViewportResizedMessage_className_004e8720[];
extern char g_igViewportResizedMessage_metaObject_0056dc10[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();
int igViewportResizedMessage_InitFields();

void igViewportResizedMessage_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewportResizedMessage_metaObject_0056dc10, /* published MetaObject slot */
        igMessage_Register,                             /* base class registrar */
        igMessage_GetPublishedMetaObject_00231020,      /* base class MetaObject accessor */
        thunk_igViewportResizedMessage_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igViewportResizedMessage_className_004e8720,  /* class name */
        0x18,                                           /* instance size */
        igViewportResizedMessage_GetVTable,             /* vtable getter */
        &igViewportResizedMessage_InitFields,           /* field adder */
        0,                                              /* extra callback item */
        0                                               /* callback list */
    );
}
