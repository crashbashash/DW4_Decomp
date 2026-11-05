/* 0x00139010 igColorAttr_Register: registers class igColorAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igColorAttr_GetVTable[];
extern char thunk_igColorAttr_GetMetaObject[];
extern char s_igColorAttr_className_004d5998[];
extern char g_igColorAttr_metaObject_0055f2e0[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igColorAttr_InitFields();

void igColorAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igColorAttr_metaObject_0055f2e0,                 /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igColorAttr_GetMetaObject,                   /* own MetaObject accessor (stored at +0x54) */
        s_igColorAttr_className_004d5998,                  /* class name */
        0x20,                                              /* instance size */
        igColorAttr_GetVTable,                             /* vtable getter */
        &igColorAttr_InitFields,                           /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
