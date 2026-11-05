/* 0x002bd0d0 igObjectRefMetaField_Register: registers class igObjectRefMetaField with the object system, derived from igRefMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRefMetaField_GetPublishedMetaObject_002b99d0[];
extern char igRefMetaField_Register[];
extern char igObjectRefMetaField_GetVTable[];
extern char thunk_igObjectRefMetaField_GetMetaObject[];
extern char g_igObjectRefMetaField_callbackList_004bfaa8[];
extern char s_igObjectRefMetaField_className_004f6420[];
extern char g_igObjectRefMetaField_metaObject_00585b20[];
int igMetaObject_RegisterClass();
int igObjectRefMetaField_InitFields();

void igObjectRefMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igObjectRefMetaField_metaObject_00585b20,     /* published MetaObject slot */
        igRefMetaField_Register,                        /* base class registrar */
        igRefMetaField_GetPublishedMetaObject_002b99d0, /* base class MetaObject accessor */
        thunk_igObjectRefMetaField_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igObjectRefMetaField_className_004f6420,      /* class name */
        0x44,                                           /* instance size */
        igObjectRefMetaField_GetVTable,                 /* vtable getter */
        &igObjectRefMetaField_InitFields,               /* field adder */
        0,                                              /* extra callback item */
        g_igObjectRefMetaField_callbackList_004bfaa8    /* callback list */
    );
}
