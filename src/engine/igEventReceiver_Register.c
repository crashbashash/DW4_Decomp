/* 0x00451330 igEventReceiver_Register: registers class igEventReceiver with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igEventReceiver_GetVTable[];
extern char thunk_igEventReceiver_GetMetaObject[];
extern char igEventReceiver_className[];
extern char g_igEventReceiver_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igEventReceiver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igEventReceiver_metaObject, /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igEventReceiver_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igEventReceiver_className,  /* class name */
        8,                                     /* instance size */
        igEventReceiver_GetVTable,             /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
