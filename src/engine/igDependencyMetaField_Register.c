/* 0x002c80a0 igDependencyMetaField_Register: registers class igDependencyMetaField with the object system, derived from igCompoundMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igCompoundMetaField_GetPublishedMetaObject[];
extern char igDependencyMetaField_GetVTable[];
extern char thunk_igDependencyMetaField_GetMetaObject[];
extern char igCompoundMetaField_Register[];
extern char g_igDependencyMetaField_callbackList[];
extern char igDependencyMetaField_className[];
extern char g_igDependencyMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igDependencyMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDependencyMetaField_metaObject,         /* published MetaObject slot */
        igCompoundMetaField_Register,                        /* base class registrar */
        igCompoundMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igDependencyMetaField_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        igDependencyMetaField_className,          /* class name */
        0x38,                                                /* instance size */
        igDependencyMetaField_GetVTable,                     /* vtable getter */
        0,                                                   /* field adder */
        0,                                                   /* extra callback item */
        g_igDependencyMetaField_callbackList        /* callback list */
    );
}
