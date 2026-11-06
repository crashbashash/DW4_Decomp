/* 0x001a3de0 igCommonTraversal_Register: registers class igCommonTraversal with the object system, derived from igTraversal.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igTraversal_Register[];
extern char igTraversal_GetPublishedMetaObject[];
extern char igCommonTraversal_GetVTable[];
extern char thunk_igCommonTraversal_GetMetaObject[];
extern char g_igCommonTraversal_callbackList[];
extern char igCommonTraversal_className[];
extern char g_igCommonTraversal_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCommonTraversal_InitFields();
int FUN_001a44d0();

void igCommonTraversal_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCommonTraversal_metaObject,     /* published MetaObject slot */
        igTraversal_Register,                        /* base class registrar */
        igTraversal_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igCommonTraversal_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igCommonTraversal_className,      /* class name */
        0x1D8,                                       /* instance size */
        igCommonTraversal_GetVTable,                 /* vtable getter */
        &igCommonTraversal_InitFields,               /* field adder */
        &FUN_001a44d0,                               /* extra callback item */
        g_igCommonTraversal_callbackList    /* callback list */
    );
}
