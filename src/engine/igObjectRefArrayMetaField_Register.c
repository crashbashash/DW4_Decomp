/* 0x002bd480 igObjectRefArrayMetaField_Register: registers class igObjectRefArrayMetaField with the object system, derived from igObjectRefMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectRefMetaField_Register[];
extern char igObjectRefArrayMetaField_GetVTable[];
extern char thunk_igObjectRefArrayMetaField_GetMetaObject[];
extern char igObjectRefMetaField_GetPublishedMetaObject_002bd510[];
extern char g_igObjectRefArrayMetaField_callbackList_004bfaf8[];
extern char s_igObjectRefArrayMetaField_className_004f6460[];
extern char g_igObjectRefArrayMetaField_metaObject_00585b48[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igObjectRefArrayMetaField_InitFields();

void igObjectRefArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                    /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igObjectRefArrayMetaField_metaObject_00585b48,      /* published MetaObject slot */
        igObjectRefMetaField_Register,                        /* base class registrar */
        igObjectRefMetaField_GetPublishedMetaObject_002bd510, /* base class MetaObject accessor */
        thunk_igObjectRefArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igObjectRefArrayMetaField_className_004f6460,       /* class name */
        0x48,                                                 /* instance size */
        igObjectRefArrayMetaField_GetVTable,                  /* vtable getter */
        &igObjectRefArrayMetaField_InitFields,                /* field adder */
        0,                                                    /* extra callback item */
        g_igObjectRefArrayMetaField_callbackList_004bfaf8     /* callback list */
    );
}
