/* 0x002c4720 igFloatMetaField_Register: registers class igFloatMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject_00187180[];
extern char igMetaField_Register[];
extern char igFloatMetaField_GetVTable[];
extern char thunk_igFloatMetaField_GetMetaObject[];
extern char g_igFloatMetaField_callbackList_004c0ab8[];
extern char s_igFloatMetaField_className_004f75e0[];
extern char g_igFloatMetaField_metaObject_00586378[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igFloatMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFloatMetaField_metaObject_00586378,      /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject_00187180, /* base class MetaObject accessor */
        thunk_igFloatMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igFloatMetaField_className_004f75e0,       /* class name */
        0x34,                                        /* instance size */
        igFloatMetaField_GetVTable,                  /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igFloatMetaField_callbackList_004c0ab8     /* callback list */
    );
}
