/* 0x002278b0 igIterateField_Register: registers class igIterateField with the object system, derived from igIterator.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igIterator_Register[];
extern char igIterator_GetPublishedMetaObject[];
extern char igIterateField_GetVTable[];
extern char thunk_igIterateField_GetMetaObject[];
extern char g_igIterateField_callbackList[];
extern char igIterateField_className[];
extern char g_igIterateField_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igIterateField_InitFields();

void igIterateField_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIterateField_metaObject,       /* published MetaObject slot */
        igIterator_Register,                        /* base class registrar */
        igIterator_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igIterateField_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igIterateField_className,        /* class name */
        0x10,                                       /* instance size */
        igIterateField_GetVTable,                   /* vtable getter */
        &igIterateField_InitFields,                 /* field adder */
        0,                                          /* extra callback item */
        g_igIterateField_callbackList      /* callback list */
    );
}
