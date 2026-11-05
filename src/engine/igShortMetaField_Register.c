/* 0x002ba190 igShortMetaField_Register: registers class igShortMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject_00187180[];
extern char igShortMetaField_GetVTable[];
extern char thunk_igShortMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igShortMetaField_callbackList_004bf6e8[];
extern char s_igShortMetaField_className_004f5f70[];
extern char g_igShortMetaField_metaObject_00585948[];
int igMetaObject_RegisterClass();

void igShortMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igShortMetaField_metaObject_00585948,      /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject_00187180, /* base class MetaObject accessor */
        thunk_igShortMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igShortMetaField_className_004f5f70,       /* class name */
        0x34,                                        /* instance size */
        igShortMetaField_GetVTable,                  /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igShortMetaField_callbackList_004bf6e8     /* callback list */
    );
}
