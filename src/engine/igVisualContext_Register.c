/* 0x0014a0f0 igVisualContext_Register: registers class igVisualContext with the object system, derived from igContext.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char thunk_igVisualContext_GetMetaObject[];
extern char igContext_GetPublishedMetaObject[];
extern char igContext_Register[];
extern char g_igVisualContext_callbackList[];
extern char igVisualContext_className[];
extern char g_igVisualContext_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igVisualContext_InitFields();

void igVisualContext_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVisualContext_metaObject,     /* published MetaObject slot */
        igContext_Register,                        /* base class registrar */
        igContext_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igVisualContext_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igVisualContext_className,      /* class name */
        0x140,                                     /* instance size */
        0,                                         /* vtable getter */
        &igVisualContext_InitFields,               /* field adder */
        0,                                         /* extra callback item */
        g_igVisualContext_callbackList    /* callback list */
    );
}
