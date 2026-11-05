/* 0x00133520 igStencilStateAttr_Register: registers class igStencilStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igStencilStateAttr_GetVTable[];
extern char thunk_igStencilStateAttr_GetMetaObject[];
extern char s_igStencilStateAttr_className_004d4ea0[];
extern char g_igStencilStateAttr_metaObject_0055ee40[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igStencilStateAttr_InitFields();

void igStencilStateAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStencilStateAttr_metaObject_0055ee40,          /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igStencilStateAttr_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        s_igStencilStateAttr_className_004d4ea0,           /* class name */
        0x10,                                              /* instance size */
        igStencilStateAttr_GetVTable,                      /* vtable getter */
        &igStencilStateAttr_InitFields,                    /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
