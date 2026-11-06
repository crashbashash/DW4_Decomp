/* 0x001387c0 igCullFaceAttr_Register: registers class igCullFaceAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igCullFaceAttr_GetVTable[];
extern char thunk_igCullFaceAttr_GetMetaObject[];
extern char igCullFaceAttr_className[];
extern char g_igCullFaceAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCullFaceAttr_InitFields();

void igCullFaceAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCullFaceAttr_metaObject,              /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igCullFaceAttr_GetMetaObject,                /* own MetaObject accessor (stored at +0x54) */
        igCullFaceAttr_className,               /* class name */
        0x14,                                              /* instance size */
        igCullFaceAttr_GetVTable,                          /* vtable getter */
        &igCullFaceAttr_InitFields,                        /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
