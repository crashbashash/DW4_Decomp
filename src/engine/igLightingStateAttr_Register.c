/* 0x00135f50 igLightingStateAttr_Register: registers class igLightingStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igLightingStateAttr_GetVTable[];
extern char thunk_igLightingStateAttr_GetMetaObject[];
extern char igLightingStateAttr_className[];
extern char g_igLightingStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igLightingStateAttr_InitFields();

void igLightingStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLightingStateAttr_metaObject,         /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igLightingStateAttr_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        igLightingStateAttr_className,          /* class name */
        0x10,                                              /* instance size */
        igLightingStateAttr_GetVTable,                     /* vtable getter */
        &igLightingStateAttr_InitFields,                   /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
