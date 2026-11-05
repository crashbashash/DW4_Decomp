/* 0x002cccb0 igBoolMetaField_Register: registers class igBoolMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject_00187180[];
extern char igMetaField_Register[];
extern char igBoolMetaField_GetVTable[];
extern char thunk_igBoolMetaField_GetMetaObject[];
extern char g_igBoolMetaField_callbackList_004c1570[];
extern char s_igBoolMetaField_className_004f8800[];
extern char g_igBoolMetaField_metaObject_00586988[];
int igMetaObject_RegisterClass();

void igBoolMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBoolMetaField_metaObject_00586988,       /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject_00187180, /* base class MetaObject accessor */
        thunk_igBoolMetaField_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igBoolMetaField_className_004f8800,        /* class name */
        0x34,                                        /* instance size */
        igBoolMetaField_GetVTable,                   /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igBoolMetaField_callbackList_004c1570      /* callback list */
    );
}
