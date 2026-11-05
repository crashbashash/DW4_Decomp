/* 0x002b9950 igStringMetaField_Register: registers class igStringMetaField with the object system, derived from igRefMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igStringMetaField_GetVTable[];
extern char thunk_igStringMetaField_GetMetaObject[];
extern char igRefMetaField_GetPublishedMetaObject_002b99d0[];
extern char igRefMetaField_Register[];
extern char g_igStringMetaField_callbackList_004bf698[];
extern char s_igStringMetaField_className_004f5ef0[];
extern char g_igStringMetaField_metaObject_00585908[];
int igMetaObject_RegisterClass();
int igStringMetaField_InitFields();

void igStringMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStringMetaField_metaObject_00585908,        /* published MetaObject slot */
        igRefMetaField_Register,                        /* base class registrar */
        igRefMetaField_GetPublishedMetaObject_002b99d0, /* base class MetaObject accessor */
        thunk_igStringMetaField_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        s_igStringMetaField_className_004f5ef0,         /* class name */
        0x3C,                                           /* instance size */
        igStringMetaField_GetVTable,                    /* vtable getter */
        &igStringMetaField_InitFields,                  /* field adder */
        0,                                              /* extra callback item */
        g_igStringMetaField_callbackList_004bf698       /* callback list */
    );
}
