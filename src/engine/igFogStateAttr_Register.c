/* 0x00137cb0 igFogStateAttr_Register: registers class igFogStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igFogStateAttr_GetVTable[];
extern char thunk_igFogStateAttr_GetMetaObject[];
extern char igFogStateAttr_className[];
extern char g_igFogStateAttr_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igFogStateAttr_InitFields();

void igFogStateAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFogStateAttr_metaObject,              /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igFogStateAttr_GetMetaObject,                /* own MetaObject accessor (stored at +0x54) */
        igFogStateAttr_className,               /* class name */
        0x10,                                              /* instance size */
        igFogStateAttr_GetVTable,                          /* vtable getter */
        &igFogStateAttr_InitFields,                        /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
