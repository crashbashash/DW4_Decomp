/* 0x00133f90 igRenderListAttr_Register: registers class igRenderListAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igRenderListAttr_GetVTable[];
extern char thunk_igRenderListAttr_GetMetaObject[];
extern char g_igRenderListAttr_callbackList_00485f60[];
extern char s_igRenderListAttr_className_004d4fe0[];
extern char g_igRenderListAttr_metaObject_0055eeb0[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igRenderListAttr_InitFields();

void igRenderListAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRenderListAttr_metaObject_0055eeb0,            /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igRenderListAttr_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        s_igRenderListAttr_className_004d4fe0,             /* class name */
        0x14,                                              /* instance size */
        igRenderListAttr_GetVTable,                        /* vtable getter */
        &igRenderListAttr_InitFields,                      /* field adder */
        0,                                                 /* extra callback item */
        g_igRenderListAttr_callbackList_00485f60           /* callback list */
    );
}
