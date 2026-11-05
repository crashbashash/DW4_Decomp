/* 0x001314c0 igTextureStateAttr_Register: registers class igTextureStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igTextureStateAttr_GetVTable[];
extern char thunk_igTextureStateAttr_GetMetaObject[];
extern char s_igTextureStateAttr_className_004d4c00[];
extern char g_igTextureStateAttr_metaObject_0055eca8[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igTextureStateAttr_InitFields();

void igTextureStateAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTextureStateAttr_metaObject_0055eca8,          /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igTextureStateAttr_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        s_igTextureStateAttr_className_004d4c00,           /* class name */
        0x14,                                              /* instance size */
        igTextureStateAttr_GetVTable,                      /* vtable getter */
        &igTextureStateAttr_InitFields,                    /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
