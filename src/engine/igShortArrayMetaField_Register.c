/* 0x002ba450 igShortArrayMetaField_Register: registers class igShortArrayMetaField with the object system, derived from igShortMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igShortMetaField_Register[];
extern char igShortArrayMetaField_GetVTable[];
extern char thunk_igShortArrayMetaField_GetMetaObject[];
extern char igShortMetaField_GetPublishedMetaObject_002ba4e0[];
extern char g_igShortArrayMetaField_callbackList_004bf6f0[];
extern char s_igShortArrayMetaField_className_004f5f90[];
extern char g_igShortArrayMetaField_metaObject_00585958[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igShortArrayMetaField_InitFields();

void igShortArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igShortArrayMetaField_metaObject_00585958,      /* published MetaObject slot */
        igShortMetaField_Register,                        /* base class registrar */
        igShortMetaField_GetPublishedMetaObject_002ba4e0, /* base class MetaObject accessor */
        thunk_igShortArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igShortArrayMetaField_className_004f5f90,       /* class name */
        0x38,                                             /* instance size */
        igShortArrayMetaField_GetVTable,                  /* vtable getter */
        &igShortArrayMetaField_InitFields,                /* field adder */
        0,                                                /* extra callback item */
        g_igShortArrayMetaField_callbackList_004bf6f0     /* callback list */
    );
}
