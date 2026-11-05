/* 0x002c64f0 igEnumArrayMetaField_Register: registers class igEnumArrayMetaField with the object system, derived from igEnumMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igEnumMetaField_Register[];
extern char igEnumArrayMetaField_GetVTable[];
extern char thunk_igEnumArrayMetaField_GetMetaObject[];
extern char igEnumMetaField_GetPublishedMetaObject_002c6580[];
extern char g_igEnumArrayMetaField_callbackList_004c0f90[];
extern char s_igEnumArrayMetaField_className_004f7eb0[];
extern char g_igEnumArrayMetaField_metaObject_005865b0[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igEnumArrayMetaField_InitFields();

void igEnumArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igEnumArrayMetaField_metaObject_005865b0,      /* published MetaObject slot */
        igEnumMetaField_Register,                        /* base class registrar */
        igEnumMetaField_GetPublishedMetaObject_002c6580, /* base class MetaObject accessor */
        thunk_igEnumArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igEnumArrayMetaField_className_004f7eb0,       /* class name */
        0x3C,                                            /* instance size */
        igEnumArrayMetaField_GetVTable,                  /* vtable getter */
        &igEnumArrayMetaField_InitFields,                /* field adder */
        0,                                               /* extra callback item */
        g_igEnumArrayMetaField_callbackList_004c0f90     /* callback list */
    );
}
