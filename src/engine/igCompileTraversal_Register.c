/* 0x001a3180 igCompileTraversal_Register: registers class igCompileTraversal with the object system, derived from igCommonTraversal.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igCommonTraversal_GetPublishedMetaObject[];
extern char igCompileTraversal_GetVTable[];
extern char thunk_igCompileTraversal_GetMetaObject[];
extern char igCommonTraversal_Register[];
extern char g_igCompileTraversal_callbackList[];
extern char igCompileTraversal_className[];
extern char g_igCompileTraversal_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCompileTraversal_InitFields();
int FUN_001a33e0();

void igCompileTraversal_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCompileTraversal_metaObject,          /* published MetaObject slot */
        igCommonTraversal_Register,                        /* base class registrar */
        igCommonTraversal_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igCompileTraversal_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        igCompileTraversal_className,           /* class name */
        0x208,                                             /* instance size */
        igCompileTraversal_GetVTable,                      /* vtable getter */
        &igCompileTraversal_InitFields,                    /* field adder */
        &FUN_001a33e0,                                     /* extra callback item */
        g_igCompileTraversal_callbackList         /* callback list */
    );
}
