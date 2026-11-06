/* 0x002bf690 igMemoryRefMetaField_Register: registers class igMemoryRefMetaField with the object system, derived from igRefMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRefMetaField_GetPublishedMetaObject[];
extern char igRefMetaField_Register[];
extern char igMemoryRefMetaField_GetVTable[];
extern char thunk_igMemoryRefMetaField_GetMetaObject[];
extern char g_igMemoryRefMetaField_callbackList[];
extern char igMemoryRefMetaField_className[];
extern char g_igMemoryRefMetaField_metaObject[];
int igMetaObject_RegisterClass();
extern int igMemoryRefMetaField_InitFields_002bf710[4];
void igMemoryRefMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMemoryRefMetaField_metaObject,     /* published MetaObject slot */
        igRefMetaField_Register,                        /* base class registrar */
        igRefMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igMemoryRefMetaField_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igMemoryRefMetaField_className,      /* class name */
        0x50,                                           /* instance size */
        igMemoryRefMetaField_GetVTable,                 /* vtable getter */
        &igMemoryRefMetaField_InitFields_002bf710[0],   /* field adder (igMetaObject_CreateFields) */
        0,                                              /* extra callback item */
        g_igMemoryRefMetaField_callbackList    /* callback list */
    );
}
