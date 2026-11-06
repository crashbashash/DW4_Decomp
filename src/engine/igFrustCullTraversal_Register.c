/* 0x001a1180 igFrustCullTraversal_Register: registers class igFrustCullTraversal with the object system, derived from igCommonTraversal.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igFrustCullTraversal_GetVTable[];
extern char thunk_igFrustCullTraversal_GetMetaObject[];
extern char igCommonTraversal_GetPublishedMetaObject[];
extern char igCommonTraversal_Register[];
extern char g_igFrustCullTraversal_callbackList[];
extern char igFrustCullTraversal_className[];
extern char g_igFrustCullTraversal_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igFrustCullTraversal_InitFields();
int FUN_001a13a0();

void igFrustCullTraversal_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFrustCullTraversal_metaObject,        /* published MetaObject slot */
        igCommonTraversal_Register,                        /* base class registrar */
        igCommonTraversal_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igFrustCullTraversal_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igFrustCullTraversal_className,         /* class name */
        0x230,                                             /* instance size */
        igFrustCullTraversal_GetVTable,                    /* vtable getter */
        &igFrustCullTraversal_InitFields,                  /* field adder */
        &FUN_001a13a0,                                     /* extra callback item */
        g_igFrustCullTraversal_callbackList       /* callback list */
    );
}
