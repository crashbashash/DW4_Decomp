/* 0x00227b00 igIterateDerived_Register: registers class igIterateDerived with the object system, derived from igIterator.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igIterator_Register[];
extern char igIterator_GetPublishedMetaObject[];
extern char igIterateDerived_GetVTable[];
extern char thunk_igIterateDerived_GetMetaObject[];
extern char g_igIterateDerived_callbackList[];
extern char igIterateDerived_className[];
extern char g_igIterateDerived_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igIterateDerived_InitFields();

void igIterateDerived_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIterateDerived_metaObject,     /* published MetaObject slot */
        igIterator_Register,                        /* base class registrar */
        igIterator_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igIterateDerived_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igIterateDerived_className,      /* class name */
        0x10,                                       /* instance size */
        igIterateDerived_GetVTable,                 /* vtable getter */
        &igIterateDerived_InitFields,               /* field adder */
        0,                                          /* extra callback item */
        g_igIterateDerived_callbackList    /* callback list */
    );
}
