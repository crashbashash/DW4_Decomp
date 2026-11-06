/* 0x0044c770 igRenderer_Register: registers class igRenderer with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char thunk_igRenderer_GetMetaObject[];
extern char g_igRenderer_callbackList[];
extern char igRenderer_className[];
extern char g_igRenderer_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igRenderer_InitFields();

void igRenderer_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRenderer_metaObject,      /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igRenderer_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igRenderer_className,       /* class name */
        0xC,                                   /* instance size */
        0,                                     /* vtable getter */
        &igRenderer_InitFields,                /* field adder */
        0,                                     /* extra callback item */
        g_igRenderer_callbackList     /* callback list */
    );
}
