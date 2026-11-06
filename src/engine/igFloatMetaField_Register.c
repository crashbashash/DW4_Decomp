/* 0x002c4720 igFloatMetaField_Register: registers class igFloatMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject[];
extern char igMetaField_Register[];
extern char igFloatMetaField_GetVTable[];
extern char thunk_igFloatMetaField_GetMetaObject[];
extern char g_igFloatMetaField_callbackList[];
extern char igFloatMetaField_className[];
extern char g_igFloatMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igFloatMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFloatMetaField_metaObject,      /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igFloatMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igFloatMetaField_className,       /* class name */
        0x34,                                        /* instance size */
        igFloatMetaField_GetVTable,                  /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igFloatMetaField_callbackList     /* callback list */
    );
}
