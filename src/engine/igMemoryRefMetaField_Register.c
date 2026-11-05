/* 0x002bf690 igMemoryRefMetaField_Register: registers class igMemoryRefMetaField with the object system, derived from igRefMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRefMetaField_GetPublishedMetaObject_002b99d0[];
extern char igRefMetaField_Register[];
extern char igMemoryRefMetaField_GetVTable[];
extern char thunk_igMemoryRefMetaField_GetMetaObject[];
extern char g_igMemoryRefMetaField_callbackList_004bff88[];
extern char s_igMemoryRefMetaField_className_004f6920[];
extern char g_igMemoryRefMetaField_metaObject_00585d80[];
int igMetaObject_RegisterClass();
extern int igMemoryRefMetaField_InitFields_002bf710[4];
void igMemoryRefMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMemoryRefMetaField_metaObject_00585d80,     /* published MetaObject slot */
        igRefMetaField_Register,                        /* base class registrar */
        igRefMetaField_GetPublishedMetaObject_002b99d0, /* base class MetaObject accessor */
        thunk_igMemoryRefMetaField_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igMemoryRefMetaField_className_004f6920,      /* class name */
        0x50,                                           /* instance size */
        igMemoryRefMetaField_GetVTable,                 /* vtable getter */
        &igMemoryRefMetaField_InitFields_002bf710[0],   /* field adder (igMetaObject_CreateFields) */
        0,                                              /* extra callback item */
        g_igMemoryRefMetaField_callbackList_004bff88    /* callback list */
    );
}
