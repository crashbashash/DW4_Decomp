/* 0x0013b3a0 igAlphaStateAttr_Register: registers class igAlphaStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igAlphaStateAttr_GetVTable[];
extern char thunk_igAlphaStateAttr_GetMetaObject[];
extern char s_igAlphaStateAttr_className_004d5da0[];
extern char g_igAlphaStateAttr_metaObject_0055f480[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igAlphaStateAttr_InitFields();

void igAlphaStateAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAlphaStateAttr_metaObject_0055f480,            /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igAlphaStateAttr_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        s_igAlphaStateAttr_className_004d5da0,             /* class name */
        0x10,                                              /* instance size */
        igAlphaStateAttr_GetVTable,                        /* vtable getter */
        &igAlphaStateAttr_InitFields,                      /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
