/* 0x002b9d90 igStringArrayMetaField_Register: registers class igStringArrayMetaField with the object system, derived from igStringMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igStringMetaField_Register[];
extern char igStringArrayMetaField_GetVTable[];
extern char thunk_igStringArrayMetaField_GetMetaObject[];
extern char igStringMetaField_GetPublishedMetaObject_002b9e20[];
extern char g_igStringArrayMetaField_callbackList_004bf6c0[];
extern char s_igStringArrayMetaField_className_004f5f50[];
extern char g_igStringArrayMetaField_metaObject_00585930[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igStringArrayMetaField_InitFields();

void igStringArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStringArrayMetaField_metaObject_00585930,      /* published MetaObject slot */
        igStringMetaField_Register,                        /* base class registrar */
        igStringMetaField_GetPublishedMetaObject_002b9e20, /* base class MetaObject accessor */
        thunk_igStringArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igStringArrayMetaField_className_004f5f50,       /* class name */
        0x40,                                              /* instance size */
        igStringArrayMetaField_GetVTable,                  /* vtable getter */
        &igStringArrayMetaField_InitFields,                /* field adder */
        0,                                                 /* extra callback item */
        g_igStringArrayMetaField_callbackList_004bf6c0     /* callback list */
    );
}
