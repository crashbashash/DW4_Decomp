/* 0x00137cb0 igFogStateAttr_Register: registers class igFogStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igFogStateAttr_GetVTable[];
extern char thunk_igFogStateAttr_GetMetaObject[];
extern char s_igFogStateAttr_className_004d5720[];
extern char g_igFogStateAttr_metaObject_0055f1c8[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igFogStateAttr_InitFields();

void igFogStateAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFogStateAttr_metaObject_0055f1c8,              /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igFogStateAttr_GetMetaObject,                /* own MetaObject accessor (stored at +0x54) */
        s_igFogStateAttr_className_004d5720,               /* class name */
        0x10,                                              /* instance size */
        igFogStateAttr_GetVTable,                          /* vtable getter */
        &igFogStateAttr_InitFields,                        /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
