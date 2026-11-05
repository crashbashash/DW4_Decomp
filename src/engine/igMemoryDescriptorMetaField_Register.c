/* 0x002ce6e0 igMemoryDescriptorMetaField_Register: registers class igMemoryDescriptorMetaField with the object system, derived from igCompoundMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igCompoundMetaField_GetPublishedMetaObject_0014e530[];
extern char igCompoundMetaField_Register[];
extern char igMemoryDescriptorMetaField_GetVTable[];
extern char thunk_igMemoryDescriptorMetaField_GetMetaObject[];
extern char g_igMemoryDescriptorMetaField_callbackList_004c1af8[];
extern char s_igMemoryDescriptorMetaField_className_004f8ca0[];
extern char g_igMemoryDescriptorMetaField_metaObject_00586bd8[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igMemoryDescriptorMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMemoryDescriptorMetaField_metaObject_00586bd8,   /* published MetaObject slot */
        igCompoundMetaField_Register,                        /* base class registrar */
        igCompoundMetaField_GetPublishedMetaObject_0014e530, /* base class MetaObject accessor */
        thunk_igMemoryDescriptorMetaField_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igMemoryDescriptorMetaField_className_004f8ca0,    /* class name */
        0x38,                                                /* instance size */
        igMemoryDescriptorMetaField_GetVTable,               /* vtable getter */
        0,                                                   /* field adder */
        0,                                                   /* extra callback item */
        g_igMemoryDescriptorMetaField_callbackList_004c1af8  /* callback list */
    );
}
