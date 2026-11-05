/* 0x00139730 igBlendStateAttr_Register: registers class igBlendStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igBlendStateAttr_GetVTable[];
extern char thunk_igBlendStateAttr_GetMetaObject[];
extern char s_igBlendStateAttr_className_004d5a20[];
extern char g_igBlendStateAttr_metaObject_0055f348[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igBlendStateAttr_InitFields();

void igBlendStateAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBlendStateAttr_metaObject_0055f348,            /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igBlendStateAttr_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        s_igBlendStateAttr_className_004d5a20,             /* class name */
        0x10,                                              /* instance size */
        igBlendStateAttr_GetVTable,                        /* vtable getter */
        &igBlendStateAttr_InitFields,                      /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
