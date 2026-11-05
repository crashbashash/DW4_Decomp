/* 0x00137e40 igFogAttr_Register: registers class igFogAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igFogAttr_GetVTable[];
extern char thunk_igFogAttr_GetMetaObject[];
extern char s_igFogAttr_className_004d5730[];
extern char g_igFogAttr_metaObject_0055f1d8[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igFogAttr_InitFields();

void igFogAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFogAttr_metaObject_0055f1d8,                   /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igFogAttr_GetMetaObject,                     /* own MetaObject accessor (stored at +0x54) */
        s_igFogAttr_className_004d5730,                    /* class name */
        0x2C,                                              /* instance size */
        igFogAttr_GetVTable,                               /* vtable getter */
        &igFogAttr_InitFields,                             /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
