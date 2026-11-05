/* 0x001332a0 igTexGenMatrixAttr_Register: registers class igTexGenMatrixAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igTexGenMatrixAttr_GetVTable[];
extern char thunk_igTexGenMatrixAttr_GetMetaObject[];
extern char s_igTexGenMatrixAttr_className_004d4e80[];
extern char g_igTexGenMatrixAttr_metaObject_0055ee28[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igTexGenMatrixAttr_InitFields();

void igTexGenMatrixAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTexGenMatrixAttr_metaObject_0055ee28,          /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igTexGenMatrixAttr_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        s_igTexGenMatrixAttr_className_004d4e80,           /* class name */
        0x50,                                              /* instance size */
        igTexGenMatrixAttr_GetVTable,                      /* vtable getter */
        &igTexGenMatrixAttr_InitFields,                    /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
