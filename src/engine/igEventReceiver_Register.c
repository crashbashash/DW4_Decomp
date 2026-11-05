/* 0x00451330 igEventReceiver_Register: registers class igEventReceiver with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igEventReceiver_GetVTable[];
extern char thunk_igEventReceiver_GetMetaObject[];
extern char s_igEventReceiver_className_0051e570[];
extern char g_igEventReceiver_metaObject_0058c570[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();

void igEventReceiver_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igEventReceiver_metaObject_0058c570, /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igEventReceiver_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igEventReceiver_className_0051e570,  /* class name */
        8,                                     /* instance size */
        igEventReceiver_GetVTable,             /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
