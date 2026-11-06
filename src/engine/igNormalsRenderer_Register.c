/* 0x0045da00 igNormalsRenderer_Register: registers class igNormalsRenderer with the object system, derived from igRenderer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRenderer_GetPublishedMetaObject[];
extern char igRenderer_Register[];
extern char igNormalsRenderer_GetVTable[];
extern char thunk_igNormalsRenderer_GetMetaObject[];
extern char g_igNormalsRenderer_callbackList[];
extern char igNormalsRenderer_className[];
extern char g_igNormalsRenderer_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igNormalsRenderer_InitFields();

void igNormalsRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNormalsRenderer_metaObject,    /* published MetaObject slot */
        igRenderer_Register,                        /* base class registrar */
        igRenderer_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igNormalsRenderer_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        igNormalsRenderer_className,     /* class name */
        0x30,                                       /* instance size */
        igNormalsRenderer_GetVTable,                /* vtable getter */
        &igNormalsRenderer_InitFields,              /* field adder */
        0,                                          /* extra callback item */
        g_igNormalsRenderer_callbackList   /* callback list */
    );
}
