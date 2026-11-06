/* 0x0019e450 igIntersectTraversal_Register: registers class igIntersectTraversal with the object system, derived from igTraversal.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igTraversal_Register[];
extern char igIntersectTraversal_GetVTable[];
extern char thunk_igIntersectTraversal_GetMetaObject[];
extern char igTraversal_GetPublishedMetaObject[];
extern char g_igIntersectTraversal_callbackList[];
extern char igIntersectTraversal_className[];
extern char g_igIntersectTraversal_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igIntersectTraversal_InitFields();
int FUN_0019e640();

void igIntersectTraversal_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIntersectTraversal_metaObject,  /* published MetaObject slot */
        igTraversal_Register,                        /* base class registrar */
        igTraversal_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igIntersectTraversal_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        igIntersectTraversal_className,   /* class name */
        0x40,                                        /* instance size */
        igIntersectTraversal_GetVTable,              /* vtable getter */
        &igIntersectTraversal_InitFields,            /* field adder */
        &FUN_0019e640,                               /* extra callback item */
        g_igIntersectTraversal_callbackList  /* callback list */
    );
}
