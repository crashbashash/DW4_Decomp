/* 0x002bd0d0 igObjectRefMetaField_Register: registers class igObjectRefMetaField with the object system, derived from igRefMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRefMetaField_GetPublishedMetaObject[];
extern char igRefMetaField_Register[];
extern char igObjectRefMetaField_GetVTable[];
extern char thunk_igObjectRefMetaField_GetMetaObject[];
extern char g_igObjectRefMetaField_callbackList[];
extern char igObjectRefMetaField_className[];
extern char g_igObjectRefMetaField_metaObject[];
int igMetaObject_RegisterClass();
int igObjectRefMetaField_InitFields();

void igObjectRefMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igObjectRefMetaField_metaObject,     /* published MetaObject slot */
        igRefMetaField_Register,                        /* base class registrar */
        igRefMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igObjectRefMetaField_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igObjectRefMetaField_className,      /* class name */
        0x44,                                           /* instance size */
        igObjectRefMetaField_GetVTable,                 /* vtable getter */
        &igObjectRefMetaField_InitFields,               /* field adder */
        0,                                              /* extra callback item */
        g_igObjectRefMetaField_callbackList    /* callback list */
    );
}
