/* 0x00450b40 igFieldSynchronizer_Register: registers class igFieldSynchronizer with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igFieldSynchronizer_GetVTable[];
extern char thunk_igFieldSynchronizer_GetMetaObject[];
extern char g_igFieldSynchronizer_callbackList[];
extern char igFieldSynchronizer_className[];
extern char g_igFieldSynchronizer_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igFieldSynchronizer_InitFields();

void igFieldSynchronizer_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFieldSynchronizer_metaObject, /* published MetaObject slot */
        igObject_Register,                         /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,     /* base class MetaObject accessor */
        thunk_igFieldSynchronizer_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igFieldSynchronizer_className,  /* class name */
        0xC,                                       /* instance size */
        igFieldSynchronizer_GetVTable,             /* vtable getter */
        &igFieldSynchronizer_InitFields,           /* field adder */
        0,                                         /* extra callback item */
        g_igFieldSynchronizer_callbackList  /* callback list */
    );
}
