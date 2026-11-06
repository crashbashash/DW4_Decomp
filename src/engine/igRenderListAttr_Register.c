/* 0x00133f90 igRenderListAttr_Register: registers class igRenderListAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igRenderListAttr_GetVTable[];
extern char thunk_igRenderListAttr_GetMetaObject[];
extern char g_igRenderListAttr_callbackList[];
extern char igRenderListAttr_className[];
extern char g_igRenderListAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igRenderListAttr_InitFields();

void igRenderListAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRenderListAttr_metaObject,            /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igRenderListAttr_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        igRenderListAttr_className,             /* class name */
        0x14,                                              /* instance size */
        igRenderListAttr_GetVTable,                        /* vtable getter */
        &igRenderListAttr_InitFields,                      /* field adder */
        0,                                                 /* extra callback item */
        g_igRenderListAttr_callbackList           /* callback list */
    );
}
