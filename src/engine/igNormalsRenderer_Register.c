/* 0x0045da00 igNormalsRenderer_Register: registers class igNormalsRenderer with the object system, derived from igRenderer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRenderer_GetPublishedMetaObject_00231010[];
extern char igRenderer_Register[];
extern char igNormalsRenderer_GetVTable[];
extern char thunk_igNormalsRenderer_GetMetaObject[];
extern char g_igNormalsRenderer_callbackList_004d17f0[];
extern char s_igNormalsRenderer_className_0051f8e0[];
extern char g_igNormalsRenderer_metaObject_0058cda0[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igNormalsRenderer_InitFields();

void igNormalsRenderer_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNormalsRenderer_metaObject_0058cda0,    /* published MetaObject slot */
        igRenderer_Register,                        /* base class registrar */
        igRenderer_GetPublishedMetaObject_00231010, /* base class MetaObject accessor */
        thunk_igNormalsRenderer_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        s_igNormalsRenderer_className_0051f8e0,     /* class name */
        0x30,                                       /* instance size */
        igNormalsRenderer_GetVTable,                /* vtable getter */
        &igNormalsRenderer_InitFields,              /* field adder */
        0,                                          /* extra callback item */
        g_igNormalsRenderer_callbackList_004d17f0   /* callback list */
    );
}
