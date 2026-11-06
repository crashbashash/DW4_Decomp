/* 0x002ba190 igShortMetaField_Register: registers class igShortMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject[];
extern char igShortMetaField_GetVTable[];
extern char thunk_igShortMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igShortMetaField_callbackList[];
extern char igShortMetaField_className[];
extern char g_igShortMetaField_metaObject[];
int igMetaObject_RegisterClass();

void igShortMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igShortMetaField_metaObject,      /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igShortMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igShortMetaField_className,       /* class name */
        0x34,                                        /* instance size */
        igShortMetaField_GetVTable,                  /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igShortMetaField_callbackList     /* callback list */
    );
}
