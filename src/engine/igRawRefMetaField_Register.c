/* 0x002bbc50 igRawRefMetaField_Register: registers class igRawRefMetaField with the object system, derived from igRefMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRefMetaField_GetPublishedMetaObject[];
extern char igRefMetaField_Register[];
extern char igRawRefMetaField_GetVTable[];
extern char thunk_igRawRefMetaField_GetMetaObject[];
extern char g_igRawRefMetaField_callbackList[];
extern char igRawRefMetaField_className[];
extern char g_igRawRefMetaField_metaObject[];
int igMetaObject_RegisterClass();

void igRawRefMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRawRefMetaField_metaObject,        /* published MetaObject slot */
        igRefMetaField_Register,                        /* base class registrar */
        igRefMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igRawRefMetaField_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igRawRefMetaField_className,         /* class name */
        0x38,                                           /* instance size */
        igRawRefMetaField_GetVTable,                    /* vtable getter */
        0,                                              /* field adder */
        0,                                              /* extra callback item */
        g_igRawRefMetaField_callbackList       /* callback list */
    );
}
