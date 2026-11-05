/* 0x00451cb0 igDefaultAspectElement_Register: registers class igDefaultAspectElement with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igDefaultAspectElement_GetVTable[];
extern char thunk_igDefaultAspectElement_GetMetaObject[];
extern char g_igDefaultAspectElement_callbackList_004d07b0[];
extern char s_igDefaultAspectElement_className_0051e660[];
extern char g_igDefaultAspectElement_metaObject_0058c5b0[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igDefaultAspectElement_InitFields();

void igDefaultAspectElement_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDefaultAspectElement_metaObject_0058c5b0, /* published MetaObject slot */
        igObject_Register,                            /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,        /* base class MetaObject accessor */
        thunk_igDefaultAspectElement_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igDefaultAspectElement_className_0051e660,  /* class name */
        0x20,                                         /* instance size */
        igDefaultAspectElement_GetVTable,             /* vtable getter */
        &igDefaultAspectElement_InitFields,           /* field adder */
        0,                                            /* extra callback item */
        g_igDefaultAspectElement_callbackList_004d07b0  /* callback list */
    );
}
