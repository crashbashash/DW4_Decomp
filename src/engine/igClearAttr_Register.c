/* 0x00139450 igClearAttr_Register: registers class igClearAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igClearAttr_GetVTable[];
extern char thunk_igClearAttr_GetMetaObject[];
extern char s_igClearAttr_className_004d59d8[];
extern char g_igClearAttr_metaObject_0055f308[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igClearAttr_InitFields();

void igClearAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igClearAttr_metaObject_0055f308,                 /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igClearAttr_GetMetaObject,                   /* own MetaObject accessor (stored at +0x54) */
        s_igClearAttr_className_004d59d8,                  /* class name */
        0x48,                                              /* instance size */
        igClearAttr_GetVTable,                             /* vtable getter */
        &igClearAttr_InitFields,                           /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
