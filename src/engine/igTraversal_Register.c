/* 0x00194540 igTraversal_Register: registers class igTraversal with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igTraversal_GetVTable[];
extern char thunk_igTraversal_GetMetaObject[];
extern char igObject_Register[];
extern char g_igTraversal_callbackList_0048af00[];
extern char s_igTraversal_className_004e1210[];
extern char g_igTraversal_metaObject_00561178[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igTraversal_InitFields();
int FUN_00194690();

void igTraversal_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTraversal_metaObject_00561178,     /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igTraversal_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igTraversal_className_004e1210,      /* class name */
        0x20,                                  /* instance size */
        igTraversal_GetVTable,                 /* vtable getter */
        &igTraversal_InitFields,               /* field adder */
        &FUN_00194690,                         /* extra callback item */
        g_igTraversal_callbackList_0048af00    /* callback list */
    );
}
