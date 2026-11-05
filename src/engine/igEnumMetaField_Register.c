/* 0x002c61b0 igEnumMetaField_Register: registers class igEnumMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject_00187180[];
extern char igMetaField_Register[];
extern char igEnumMetaField_GetVTable[];
extern char thunk_igEnumMetaField_GetMetaObject[];
extern char g_igEnumMetaField_callbackList_004c0f68[];
extern char s_igEnumMetaField_className_004f7e80[];
extern char g_igEnumMetaField_metaObject_00586598[];
int igMetaObject_RegisterClass();
int igEnumMetaField_InitFields();

void igEnumMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igEnumMetaField_metaObject_00586598,       /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject_00187180, /* base class MetaObject accessor */
        thunk_igEnumMetaField_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igEnumMetaField_className_004f7e80,        /* class name */
        0x38,                                        /* instance size */
        igEnumMetaField_GetVTable,                   /* vtable getter */
        &igEnumMetaField_InitFields,                 /* field adder */
        0,                                           /* extra callback item */
        g_igEnumMetaField_callbackList_004c0f68      /* callback list */
    );
}
