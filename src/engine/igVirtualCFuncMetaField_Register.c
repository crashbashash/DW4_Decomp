/* 0x002b5e90 igVirtualCFuncMetaField_Register: registers class igVirtualCFuncMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject[];
extern char igVirtualCFuncMetaField_GetVTable[];
extern char thunk_igVirtualCFuncMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igVirtualCFuncMetaField_callbackList[];
extern char igVirtualCFuncMetaField_className[];
extern char g_igVirtualCFuncMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igVirtualCFuncMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVirtualCFuncMetaField_metaObject, /* published MetaObject slot */
        igMetaField_Register,                          /* base class registrar */
        igMetaField_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igVirtualCFuncMetaField_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igVirtualCFuncMetaField_className,  /* class name */
        0x34,                                          /* instance size */
        igVirtualCFuncMetaField_GetVTable,             /* vtable getter */
        0,                                             /* field adder */
        0,                                             /* extra callback item */
        g_igVirtualCFuncMetaField_callbackList  /* callback list */
    );
}
