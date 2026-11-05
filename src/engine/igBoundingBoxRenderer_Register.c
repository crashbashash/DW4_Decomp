/* 0x0045e060 igBoundingBoxRenderer_Register: registers class igBoundingBoxRenderer with the object system, derived from igRenderer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRenderer_GetPublishedMetaObject_00231010[];
extern char igRenderer_Register[];
extern char igBoundingBoxRenderer_GetVTable[];
extern char thunk_igBoundingBoxRenderer_GetMetaObject[];
extern char g_igBoundingBoxRenderer_callbackList_004d1920[];
extern char s_igBoundingBoxRenderer_className_0051f9b0[];
extern char g_igBoundingBoxRenderer_metaObject_0058ce18[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igBoundingBoxRenderer_InitFields();

void igBoundingBoxRenderer_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBoundingBoxRenderer_metaObject_0058ce18, /* published MetaObject slot */
        igRenderer_Register,                         /* base class registrar */
        igRenderer_GetPublishedMetaObject_00231010,  /* base class MetaObject accessor */
        thunk_igBoundingBoxRenderer_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igBoundingBoxRenderer_className_0051f9b0,  /* class name */
        0x2C,                                        /* instance size */
        igBoundingBoxRenderer_GetVTable,             /* vtable getter */
        &igBoundingBoxRenderer_InitFields,           /* field adder */
        0,                                           /* extra callback item */
        g_igBoundingBoxRenderer_callbackList_004d1920  /* callback list */
    );
}
