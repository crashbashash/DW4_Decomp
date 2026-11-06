/* 0x001a4e80 igBitMask_Register: registers class igBitMask with the object system, derived from igUnsignedIntList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igBitMask_GetVTable[];
extern char thunk_igBitMask_GetMetaObject[];
extern char igUnsignedIntList_GetPublishedMetaObject[];
extern char igUnsignedIntList_Register[];
extern char igBitMask_className[];
extern char g_igBitMask_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igBitMask_InitFields();

void igBitMask_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBitMask_metaObject,                   /* published MetaObject slot */
        igUnsignedIntList_Register,                        /* base class registrar */
        igUnsignedIntList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igBitMask_GetMetaObject,                     /* own MetaObject accessor (stored at +0x54) */
        igBitMask_className,                    /* class name */
        0x18,                                              /* instance size */
        igBitMask_GetVTable,                               /* vtable getter */
        &igBitMask_InitFields,                             /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
