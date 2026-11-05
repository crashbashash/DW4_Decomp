/* 0x002c1b20 igLongMetaField_Register: registers class igLongMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject_00187180[];
extern char igMetaField_Register[];
extern char igLongMetaField_GetVTable[];
extern char thunk_igLongMetaField_GetMetaObject[];
extern char g_igLongMetaField_callbackList_004c04e0[];
extern char s_igLongMetaField_className_004f6ef0[];
extern char g_igLongMetaField_metaObject_00586050[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igLongMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLongMetaField_metaObject_00586050,       /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject_00187180, /* base class MetaObject accessor */
        thunk_igLongMetaField_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igLongMetaField_className_004f6ef0,        /* class name */
        0x34,                                        /* instance size */
        igLongMetaField_GetVTable,                   /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igLongMetaField_callbackList_004c04e0      /* callback list */
    );
}
