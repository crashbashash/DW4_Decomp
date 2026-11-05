/* 0x001a3de0 igCommonTraversal_Register: registers class igCommonTraversal with the object system, derived from igTraversal.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igTraversal_Register[];
extern char igTraversal_GetPublishedMetaObject_0019e4e0[];
extern char igCommonTraversal_GetVTable[];
extern char thunk_igCommonTraversal_GetMetaObject[];
extern char g_igCommonTraversal_callbackList_0048c760[];
extern char s_igCommonTraversal_className_004e2ef0[];
extern char g_igCommonTraversal_metaObject_00561d78[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igCommonTraversal_InitFields();
int FUN_001a44d0();

void igCommonTraversal_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCommonTraversal_metaObject_00561d78,     /* published MetaObject slot */
        igTraversal_Register,                        /* base class registrar */
        igTraversal_GetPublishedMetaObject_0019e4e0, /* base class MetaObject accessor */
        thunk_igCommonTraversal_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igCommonTraversal_className_004e2ef0,      /* class name */
        0x1D8,                                       /* instance size */
        igCommonTraversal_GetVTable,                 /* vtable getter */
        &igCommonTraversal_InitFields,               /* field adder */
        &FUN_001a44d0,                               /* extra callback item */
        g_igCommonTraversal_callbackList_0048c760    /* callback list */
    );
}
