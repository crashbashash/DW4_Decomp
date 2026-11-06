/* 0x002cc170 igCharMetaField_Register: registers class igCharMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject[];
extern char igMetaField_Register[];
extern char igCharMetaField_GetVTable[];
extern char thunk_igCharMetaField_GetMetaObject[];
extern char g_igCharMetaField_callbackList[];
extern char igCharMetaField_className[];
extern char g_igCharMetaField_metaObject[];
int igMetaObject_RegisterClass();

void igCharMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCharMetaField_metaObject,       /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igCharMetaField_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igCharMetaField_className,        /* class name */
        0x34,                                        /* instance size */
        igCharMetaField_GetVTable,                   /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igCharMetaField_callbackList      /* callback list */
    );
}
