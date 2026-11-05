/* 0x002c1da0 igLongArrayMetaField_Register: registers class igLongArrayMetaField with the object system, derived from igLongMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igLongMetaField_Register[];
extern char igLongArrayMetaField_GetVTable[];
extern char thunk_igLongArrayMetaField_GetMetaObject[];
extern char igLongMetaField_GetPublishedMetaObject_002c1e30[];
extern char g_igLongArrayMetaField_callbackList_004c04e8[];
extern char s_igLongArrayMetaField_className_004f6f00[];
extern char g_igLongArrayMetaField_metaObject_00586060[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igLongArrayMetaField_InitFields();

void igLongArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLongArrayMetaField_metaObject_00586060,      /* published MetaObject slot */
        igLongMetaField_Register,                        /* base class registrar */
        igLongMetaField_GetPublishedMetaObject_002c1e30, /* base class MetaObject accessor */
        thunk_igLongArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igLongArrayMetaField_className_004f6f00,       /* class name */
        0x38,                                            /* instance size */
        igLongArrayMetaField_GetVTable,                  /* vtable getter */
        &igLongArrayMetaField_InitFields,                /* field adder */
        0,                                               /* extra callback item */
        g_igLongArrayMetaField_callbackList_004c04e8     /* callback list */
    );
}
