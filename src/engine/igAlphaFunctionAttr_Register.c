/* 0x0013b570 igAlphaFunctionAttr_Register: registers class igAlphaFunctionAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igAlphaFunctionAttr_GetVTable[];
extern char thunk_igAlphaFunctionAttr_GetMetaObject[];
extern char igAlphaFunctionAttr_className[];
extern char g_igAlphaFunctionAttr_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igAlphaFunctionAttr_InitFields();

void igAlphaFunctionAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAlphaFunctionAttr_metaObject,         /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igAlphaFunctionAttr_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        igAlphaFunctionAttr_className,          /* class name */
        0x14,                                              /* instance size */
        igAlphaFunctionAttr_GetVTable,                     /* vtable getter */
        &igAlphaFunctionAttr_InitFields,                   /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
