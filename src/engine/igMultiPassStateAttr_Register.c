/* 0x001352c0 igMultiPassStateAttr_Register: registers class igMultiPassStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igMultiPassStateAttr_GetVTable[];
extern char thunk_igMultiPassStateAttr_GetMetaObject[];
extern char s_igMultiPassStateAttr_className_004d5340[];
extern char g_igMultiPassStateAttr_metaObject_0055efd0[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igMultiPassStateAttr_InitFields();

void igMultiPassStateAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMultiPassStateAttr_metaObject_0055efd0,        /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igMultiPassStateAttr_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        s_igMultiPassStateAttr_className_004d5340,         /* class name */
        0x10,                                              /* instance size */
        igMultiPassStateAttr_GetVTable,                    /* vtable getter */
        &igMultiPassStateAttr_InitFields,                  /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
