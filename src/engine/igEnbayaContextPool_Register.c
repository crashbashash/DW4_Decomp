/* 0x001a1cb0 igEnbayaContextPool_Register: registers class igEnbayaContextPool with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igEnbayaContextPool_GetVTable[];
extern char thunk_igEnbayaContextPool_GetMetaObject[];
extern char igObject_Register[];
extern char g_igEnbayaContextPool_callbackList_0048c2f0[];
extern char s_igEnbayaContextPool_className_004e2a50[];
extern char g_igEnbayaContextPool_metaObject_00561b60[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igEnbayaContextPool_InitFields();

void igEnbayaContextPool_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igEnbayaContextPool_metaObject_00561b60, /* published MetaObject slot */
        igObject_Register,                         /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,     /* base class MetaObject accessor */
        thunk_igEnbayaContextPool_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igEnbayaContextPool_className_004e2a50,  /* class name */
        0x14,                                      /* instance size */
        igEnbayaContextPool_GetVTable,             /* vtable getter */
        &igEnbayaContextPool_InitFields,           /* field adder */
        0,                                         /* extra callback item */
        g_igEnbayaContextPool_callbackList_0048c2f0  /* callback list */
    );
}
