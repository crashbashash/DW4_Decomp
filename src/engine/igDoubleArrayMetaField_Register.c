/* 0x002c6f50 igDoubleArrayMetaField_Register: registers class igDoubleArrayMetaField with the object system, derived from igDoubleMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDoubleMetaField_Register[];
extern char igDoubleArrayMetaField_GetVTable[];
extern char thunk_igDoubleArrayMetaField_GetMetaObject[];
extern char igDoubleMetaField_GetPublishedMetaObject_002c6fe0[];
extern char g_igDoubleArrayMetaField_callbackList_004c10c0[];
extern char s_igDoubleArrayMetaField_className_004f8120[];
extern char g_igDoubleArrayMetaField_metaObject_00586648[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igDoubleArrayMetaField_InitFields();

void igDoubleArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDoubleArrayMetaField_metaObject_00586648,      /* published MetaObject slot */
        igDoubleMetaField_Register,                        /* base class registrar */
        igDoubleMetaField_GetPublishedMetaObject_002c6fe0, /* base class MetaObject accessor */
        thunk_igDoubleArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igDoubleArrayMetaField_className_004f8120,       /* class name */
        0x38,                                              /* instance size */
        igDoubleArrayMetaField_GetVTable,                  /* vtable getter */
        &igDoubleArrayMetaField_InitFields,                /* field adder */
        0,                                                 /* extra callback item */
        g_igDoubleArrayMetaField_callbackList_004c10c0     /* callback list */
    );
}
