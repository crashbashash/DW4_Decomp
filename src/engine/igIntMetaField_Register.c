/* 0x002c2f40 igIntMetaField_Register: registers class igIntMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject[];
extern char igMetaField_Register[];
extern char igIntMetaField_GetVTable[];
extern char thunk_igIntMetaField_GetMetaObject[];
extern char g_igIntMetaField_callbackList[];
extern char igIntMetaField_className[];
extern char g_igIntMetaField_metaObject[];
int igMetaObject_RegisterClass();

void igIntMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIntMetaField_metaObject,        /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igIntMetaField_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igIntMetaField_className,         /* class name */
        0x34,                                        /* instance size */
        igIntMetaField_GetVTable,                    /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igIntMetaField_callbackList       /* callback list */
    );
}
