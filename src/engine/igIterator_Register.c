/* 0x002273e0 igIterator_Register: registers class igIterator with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igIterator_GetMetaObject[];
extern char igObject_Register[];
extern char s_igIterator_className_004e7be8[];
extern char g_igIterator_metaObject_0056d940[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();

void igIterator_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIterator_metaObject_0056d940,      /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igIterator_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igIterator_className_004e7be8,       /* class name */
        8,                                     /* instance size */
        0,                                     /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
