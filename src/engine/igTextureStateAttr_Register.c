/* 0x001314c0 igTextureStateAttr_Register: registers class igTextureStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igTextureStateAttr_GetVTable[];
extern char thunk_igTextureStateAttr_GetMetaObject[];
extern char igTextureStateAttr_className[];
extern char g_igTextureStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTextureStateAttr_InitFields();

void igTextureStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTextureStateAttr_metaObject,          /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igTextureStateAttr_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        igTextureStateAttr_className,           /* class name */
        0x14,                                              /* instance size */
        igTextureStateAttr_GetVTable,                      /* vtable getter */
        &igTextureStateAttr_InitFields,                    /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
