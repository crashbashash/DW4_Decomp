/* 0x002bb840 igRefMetaField_Register: registers class igRefMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject[];
extern char thunk_igRefMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igRefMetaField_callbackList[];
extern char igRefMetaField_className[];
extern char g_igRefMetaField_metaObject[];
int igMetaObject_RegisterClass();
int igRefMetaField_InitFields();

void igRefMetaField_Register(void) {
    igMetaObject_RegisterClass(
        1,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRefMetaField_metaObject,        /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igRefMetaField_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igRefMetaField_className,         /* class name */
        0x38,                                        /* instance size */
        0,                                           /* vtable getter */
        &igRefMetaField_InitFields,                  /* field adder */
        0,                                           /* extra callback item */
        g_igRefMetaField_callbackList       /* callback list */
    );
}
