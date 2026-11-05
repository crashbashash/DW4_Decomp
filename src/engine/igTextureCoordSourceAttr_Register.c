/* 0x001326d0 igTextureCoordSourceAttr_Register: registers class igTextureCoordSourceAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igTextureCoordSourceAttr_GetVTable[];
extern char thunk_igTextureCoordSourceAttr_GetMetaObject[];
extern char s_igTextureCoordSourceAttr_className_004d4d60[];
extern char g_igTextureCoordSourceAttr_metaObject_0055ed68[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igTextureCoordSourceAttr_InitFields();

void igTextureCoordSourceAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTextureCoordSourceAttr_metaObject_0055ed68,    /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igTextureCoordSourceAttr_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        s_igTextureCoordSourceAttr_className_004d4d60,     /* class name */
        0x18,                                              /* instance size */
        igTextureCoordSourceAttr_GetVTable,                /* vtable getter */
        &igTextureCoordSourceAttr_InitFields,              /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
