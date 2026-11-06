/* 0x0044e570 igMouseCursor_Register: registers class igMouseCursor with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igMouseCursor_GetVTable[];
extern char thunk_igMouseCursor_GetMetaObject[];
extern char g_igMouseCursor_callbackList[];
extern char igMouseCursor_className[];
extern char g_igMouseCursor_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igMouseCursor_InitFields();

void igMouseCursor_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMouseCursor_metaObject,   /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igMouseCursor_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igMouseCursor_className,    /* class name */
        0x14,                                  /* instance size */
        igMouseCursor_GetVTable,               /* vtable getter */
        &igMouseCursor_InitFields,             /* field adder */
        0,                                     /* extra callback item */
        g_igMouseCursor_callbackList  /* callback list */
    );
}
