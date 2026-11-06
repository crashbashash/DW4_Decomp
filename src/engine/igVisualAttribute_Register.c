/* 0x001303c0 igVisualAttribute_Register: registers class igVisualAttribute with the object system, derived from igAttr.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char thunk_igVisualAttribute_GetMetaObject[];
extern char igAttr_GetPublishedMetaObject[];
extern char igAttr_Register[];
extern char igVisualAttribute_className[];
extern char g_igVisualAttribute_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();

void igVisualAttribute_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        1,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVisualAttribute_metaObject, /* published MetaObject slot */
        igAttr_Register,                         /* base class registrar */
        igAttr_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igVisualAttribute_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igVisualAttribute_className,  /* class name */
        0xC,                                     /* instance size */
        0,                                       /* vtable getter */
        0,                                       /* field adder */
        0,                                       /* extra callback item */
        0                                        /* callback list */
    );
}
