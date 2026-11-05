/* 0x002bfb60 igMemoryRefArrayMetaField_Register: registers class igMemoryRefArrayMetaField with the object system, derived from igMemoryRefMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMemoryRefMetaField_Register[];
extern char igMemoryRefArrayMetaField_GetVTable[];
extern char thunk_igMemoryRefArrayMetaField_GetMetaObject[];
extern char igMemoryRefMetaField_GetPublishedMetaObject_002bfbf0[];
extern char g_igMemoryRefArrayMetaField_callbackList_004c0028[];
extern char s_igMemoryRefArrayMetaField_className_004f69a0[];
extern char g_igMemoryRefArrayMetaField_metaObject_00585de0[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igMemoryRefArrayMetaField_InitFields();

void igMemoryRefArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                    /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMemoryRefArrayMetaField_metaObject_00585de0,      /* published MetaObject slot */
        igMemoryRefMetaField_Register,                        /* base class registrar */
        igMemoryRefMetaField_GetPublishedMetaObject_002bfbf0, /* base class MetaObject accessor */
        thunk_igMemoryRefArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igMemoryRefArrayMetaField_className_004f69a0,       /* class name */
        0x54,                                                 /* instance size */
        igMemoryRefArrayMetaField_GetVTable,                  /* vtable getter */
        &igMemoryRefArrayMetaField_InitFields,                /* field adder */
        0,                                                    /* extra callback item */
        g_igMemoryRefArrayMetaField_callbackList_004c0028     /* callback list */
    );
}
