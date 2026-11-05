/* 0x002cc430 igCharArrayMetaField_Register: registers class igCharArrayMetaField with the object system, derived from igCharMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igCharMetaField_Register[];
extern char igCharArrayMetaField_GetVTable[];
extern char thunk_igCharArrayMetaField_GetMetaObject[];
extern char igCharMetaField_GetPublishedMetaObject_002cc4c0[];
extern char g_igCharArrayMetaField_callbackList_004c14f0[];
extern char s_igCharArrayMetaField_className_004f87a0[];
extern char g_igCharArrayMetaField_metaObject_00586940[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igCharArrayMetaField_InitFields();

void igCharArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCharArrayMetaField_metaObject_00586940,      /* published MetaObject slot */
        igCharMetaField_Register,                        /* base class registrar */
        igCharMetaField_GetPublishedMetaObject_002cc4c0, /* base class MetaObject accessor */
        thunk_igCharArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igCharArrayMetaField_className_004f87a0,       /* class name */
        0x38,                                            /* instance size */
        igCharArrayMetaField_GetVTable,                  /* vtable getter */
        &igCharArrayMetaField_InitFields,                /* field adder */
        0,                                               /* extra callback item */
        g_igCharArrayMetaField_callbackList_004c14f0     /* callback list */
    );
}
