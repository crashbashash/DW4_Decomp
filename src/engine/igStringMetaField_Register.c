/* 0x002b9950 igStringMetaField_Register: registers class igStringMetaField with the object system, derived from igRefMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igStringMetaField_GetVTable[];
extern char thunk_igStringMetaField_GetMetaObject[];
extern char igRefMetaField_GetPublishedMetaObject[];
extern char igRefMetaField_Register[];
extern char g_igStringMetaField_callbackList[];
extern char igStringMetaField_className[];
extern char g_igStringMetaField_metaObject[];
int igMetaObject_RegisterClass();
int igStringMetaField_InitFields();

void igStringMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStringMetaField_metaObject,        /* published MetaObject slot */
        igRefMetaField_Register,                        /* base class registrar */
        igRefMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igStringMetaField_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igStringMetaField_className,         /* class name */
        0x3C,                                           /* instance size */
        igStringMetaField_GetVTable,                    /* vtable getter */
        &igStringMetaField_InitFields,                  /* field adder */
        0,                                              /* extra callback item */
        g_igStringMetaField_callbackList       /* callback list */
    );
}
