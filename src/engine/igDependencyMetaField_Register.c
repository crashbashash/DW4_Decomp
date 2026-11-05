/* 0x002c80a0 igDependencyMetaField_Register: registers class igDependencyMetaField with the object system, derived from igCompoundMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igCompoundMetaField_GetPublishedMetaObject_0014e530[];
extern char igDependencyMetaField_GetVTable[];
extern char thunk_igDependencyMetaField_GetMetaObject[];
extern char igCompoundMetaField_Register[];
extern char g_igDependencyMetaField_callbackList_004c1378[];
extern char s_igDependencyMetaField_className_004f8420[];
extern char g_igDependencyMetaField_metaObject_00586778[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igDependencyMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDependencyMetaField_metaObject_00586778,         /* published MetaObject slot */
        igCompoundMetaField_Register,                        /* base class registrar */
        igCompoundMetaField_GetPublishedMetaObject_0014e530, /* base class MetaObject accessor */
        thunk_igDependencyMetaField_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        s_igDependencyMetaField_className_004f8420,          /* class name */
        0x38,                                                /* instance size */
        igDependencyMetaField_GetVTable,                     /* vtable getter */
        0,                                                   /* field adder */
        0,                                                   /* extra callback item */
        g_igDependencyMetaField_callbackList_004c1378        /* callback list */
    );
}
