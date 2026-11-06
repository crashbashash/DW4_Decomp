/* 0x002b8ac0 igStructMetaField_Register: registers class igStructMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject[];
extern char igStructMetaField_GetVTable[];
extern char thunk_igStructMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igStructMetaField_callbackList[];
extern char igStructMetaField_className[];
extern char g_igStructMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igStructMetaField_InitFields_002b8b50[4];
void igStructMetaField_Register(void) {
    FUN_002b5d50();  /* one-shot static-init guard (byte flag), chaining to sibling init stubs */
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStructMetaField_metaObject,     /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igStructMetaField_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igStructMetaField_className,      /* class name */
        0x40,                                        /* instance size */
        igStructMetaField_GetVTable,                 /* vtable getter */
        &igStructMetaField_InitFields_002b8b50[0],                            /* field adder: InitFields, registers the reflected fields */
        0,                                           /* extra callback item */
        g_igStructMetaField_callbackList    /* callback list */
    );
}
