/* 0x00131050 igTimeAttr_Register: registers class igTimeAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igTimeAttr_GetVTable[];
extern char thunk_igTimeAttr_GetMetaObject[];
extern char s_igTimeAttr_className_004d4bb8[];
extern char g_igTimeAttr_metaObject_0055ec80[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igTimeAttr_InitFields();

void igTimeAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTimeAttr_metaObject_0055ec80,                  /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igTimeAttr_GetMetaObject,                    /* own MetaObject accessor (stored at +0x54) */
        s_igTimeAttr_className_004d4bb8,                   /* class name */
        0x18,                                              /* instance size */
        igTimeAttr_GetVTable,                              /* vtable getter */
        &igTimeAttr_InitFields,                            /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
