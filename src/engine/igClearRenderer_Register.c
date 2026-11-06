/* 0x0044c3a0 igClearRenderer_Register: registers class igClearRenderer with the object system, derived from igRenderer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRenderer_GetPublishedMetaObject[];
extern char igClearRenderer_GetVTable[];
extern char thunk_igClearRenderer_GetMetaObject[];
extern char igRenderer_Register[];
extern char igClearRenderer_className[];
extern char g_igClearRenderer_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igClearRenderer_InitFields();

void igClearRenderer_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igClearRenderer_metaObject,      /* published MetaObject slot */
        igRenderer_Register,                        /* base class registrar */
        igRenderer_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igClearRenderer_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igClearRenderer_className,       /* class name */
        0x10,                                       /* instance size */
        igClearRenderer_GetVTable,                  /* vtable getter */
        &igClearRenderer_InitFields,                /* field adder */
        0,                                          /* extra callback item */
        0                                           /* callback list */
    );
}
