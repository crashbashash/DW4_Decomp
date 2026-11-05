/* 0x00227b00 igIterateDerived_Register: registers class igIterateDerived with the object system, derived from igIterator.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igIterator_Register[];
extern char igIterator_GetPublishedMetaObject_00227450[];
extern char igIterateDerived_GetVTable[];
extern char thunk_igIterateDerived_GetMetaObject[];
extern char g_igIterateDerived_callbackList_00497da8[];
extern char s_igIterateDerived_className_004e7c90[];
extern char g_igIterateDerived_metaObject_0056d980[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();
int igIterateDerived_InitFields();

void igIterateDerived_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIterateDerived_metaObject_0056d980,     /* published MetaObject slot */
        igIterator_Register,                        /* base class registrar */
        igIterator_GetPublishedMetaObject_00227450, /* base class MetaObject accessor */
        thunk_igIterateDerived_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igIterateDerived_className_004e7c90,      /* class name */
        0x10,                                       /* instance size */
        igIterateDerived_GetVTable,                 /* vtable getter */
        &igIterateDerived_InitFields,               /* field adder */
        0,                                          /* extra callback item */
        g_igIterateDerived_callbackList_00497da8    /* callback list */
    );
}
