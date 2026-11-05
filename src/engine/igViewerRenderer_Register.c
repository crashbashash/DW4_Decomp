/* 0x0045b0e0 igViewerRenderer_Register: registers class igViewerRenderer with the object system, derived from igRenderer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRenderer_GetPublishedMetaObject_00231010[];
extern char igRenderer_Register[];
extern char igViewerRenderer_GetVTable[];
extern char thunk_igViewerRenderer_GetMetaObject[];
extern char g_igViewerRenderer_callbackList_004d0e90[];
extern char s_igViewerRenderer_className_0051ef40[];
extern char g_igViewerRenderer_metaObject_0058c940[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igViewerRenderer_InitFields();

void igViewerRenderer_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewerRenderer_metaObject_0058c940,     /* published MetaObject slot */
        igRenderer_Register,                        /* base class registrar */
        igRenderer_GetPublishedMetaObject_00231010, /* base class MetaObject accessor */
        thunk_igViewerRenderer_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igViewerRenderer_className_0051ef40,      /* class name */
        0x5C,                                       /* instance size */
        igViewerRenderer_GetVTable,                 /* vtable getter */
        &igViewerRenderer_InitFields,               /* field adder */
        0,                                          /* extra callback item */
        g_igViewerRenderer_callbackList_004d0e90    /* callback list */
    );
}
