/* 0x002b6f20 igUnsignedIntMetaField_Register: registers class igUnsignedIntMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject_00187180[];
extern char igUnsignedIntMetaField_GetVTable[];
extern char thunk_igUnsignedIntMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igUnsignedIntMetaField_callbackList_004bf308[];
extern char s_igUnsignedIntMetaField_className_004f5b50[];
extern char g_igUnsignedIntMetaField_metaObject_00585738[];
int igMetaObject_RegisterClass();

void igUnsignedIntMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igUnsignedIntMetaField_metaObject_00585738, /* published MetaObject slot */
        igMetaField_Register,                         /* base class registrar */
        igMetaField_GetPublishedMetaObject_00187180,  /* base class MetaObject accessor */
        thunk_igUnsignedIntMetaField_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igUnsignedIntMetaField_className_004f5b50,  /* class name */
        0x34,                                         /* instance size */
        igUnsignedIntMetaField_GetVTable,             /* vtable getter */
        0,                                            /* field adder */
        0,                                            /* extra callback item */
        g_igUnsignedIntMetaField_callbackList_004bf308  /* callback list */
    );
}
