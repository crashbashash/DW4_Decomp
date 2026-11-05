/* 0x002ccf70 igBoolArrayMetaField_Register: registers class igBoolArrayMetaField with the object system, derived from igBoolMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igBoolMetaField_Register[];
extern char igBoolArrayMetaField_GetVTable[];
extern char thunk_igBoolArrayMetaField_GetMetaObject[];
extern char igBoolMetaField_GetPublishedMetaObject_002cd000[];
extern char g_igBoolArrayMetaField_callbackList_004c1578[];
extern char s_igBoolArrayMetaField_className_004f8810[];
extern char g_igBoolArrayMetaField_metaObject_00586998[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igBoolArrayMetaField_InitFields();

void igBoolArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBoolArrayMetaField_metaObject_00586998,      /* published MetaObject slot */
        igBoolMetaField_Register,                        /* base class registrar */
        igBoolMetaField_GetPublishedMetaObject_002cd000, /* base class MetaObject accessor */
        thunk_igBoolArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igBoolArrayMetaField_className_004f8810,       /* class name */
        0x38,                                            /* instance size */
        igBoolArrayMetaField_GetVTable,                  /* vtable getter */
        &igBoolArrayMetaField_InitFields,                /* field adder */
        0,                                               /* extra callback item */
        g_igBoolArrayMetaField_callbackList_004c1578     /* callback list */
    );
}
