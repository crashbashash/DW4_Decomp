/* 0x002c7bb0 igDependencyOrderedList_Register: registers class igDependencyOrderedList with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igDependencyOrderedList_GetVTable[];
extern char thunk_igDependencyOrderedList_GetMetaObject[];
extern char igObject_Register[];
extern char g_igDependencyOrderedList_callbackList[];
extern char igDependencyOrderedList_className[];
extern char g_igDependencyOrderedList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igDependencyOrderedList_InitFields();

void igDependencyOrderedList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDependencyOrderedList_metaObject, /* published MetaObject slot */
        igObject_Register,                             /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,         /* base class MetaObject accessor */
        thunk_igDependencyOrderedList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igDependencyOrderedList_className,  /* class name */
        0x1C,                                          /* instance size */
        igDependencyOrderedList_GetVTable,             /* vtable getter */
        &igDependencyOrderedList_InitFields,           /* field adder */
        0,                                             /* extra callback item */
        g_igDependencyOrderedList_callbackList  /* callback list */
    );
}
