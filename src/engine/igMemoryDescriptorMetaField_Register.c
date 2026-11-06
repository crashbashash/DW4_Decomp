/* 0x002ce6e0 igMemoryDescriptorMetaField_Register: registers class igMemoryDescriptorMetaField with the object system, derived from igCompoundMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igCompoundMetaField_GetPublishedMetaObject[];
extern char igCompoundMetaField_Register[];
extern char igMemoryDescriptorMetaField_GetVTable[];
extern char thunk_igMemoryDescriptorMetaField_GetMetaObject[];
extern char g_igMemoryDescriptorMetaField_callbackList[];
extern char igMemoryDescriptorMetaField_className[];
extern char g_igMemoryDescriptorMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igMemoryDescriptorMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMemoryDescriptorMetaField_metaObject,   /* published MetaObject slot */
        igCompoundMetaField_Register,                        /* base class registrar */
        igCompoundMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igMemoryDescriptorMetaField_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igMemoryDescriptorMetaField_className,    /* class name */
        0x38,                                                /* instance size */
        igMemoryDescriptorMetaField_GetVTable,               /* vtable getter */
        0,                                                   /* field adder */
        0,                                                   /* extra callback item */
        g_igMemoryDescriptorMetaField_callbackList  /* callback list */
    );
}
