/* 0x002bbc50 igRawRefMetaField_Register: registers class igRawRefMetaField with the object system, derived from igRefMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRefMetaField_GetPublishedMetaObject_002b99d0[];
extern char igRefMetaField_Register[];
extern char igRawRefMetaField_GetVTable[];
extern char thunk_igRawRefMetaField_GetMetaObject[];
extern char g_igRawRefMetaField_callbackList_004bf980[];
extern char s_igRawRefMetaField_className_004f6290[];
extern char g_igRawRefMetaField_metaObject_00585a80[];
int igMetaObject_RegisterClass();

void igRawRefMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRawRefMetaField_metaObject_00585a80,        /* published MetaObject slot */
        igRefMetaField_Register,                        /* base class registrar */
        igRefMetaField_GetPublishedMetaObject_002b99d0, /* base class MetaObject accessor */
        thunk_igRawRefMetaField_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        s_igRawRefMetaField_className_004f6290,         /* class name */
        0x38,                                           /* instance size */
        igRawRefMetaField_GetVTable,                    /* vtable getter */
        0,                                              /* field adder */
        0,                                              /* extra callback item */
        g_igRawRefMetaField_callbackList_004bf980       /* callback list */
    );
}
