/* 0x001a1cb0 igEnbayaContextPool_Register: registers class igEnbayaContextPool with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igEnbayaContextPool_GetVTable[];
extern char thunk_igEnbayaContextPool_GetMetaObject[];
extern char igObject_Register[];
extern char g_igEnbayaContextPool_callbackList[];
extern char igEnbayaContextPool_className[];
extern char g_igEnbayaContextPool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igEnbayaContextPool_InitFields();

void igEnbayaContextPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igEnbayaContextPool_metaObject, /* published MetaObject slot */
        igObject_Register,                         /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,     /* base class MetaObject accessor */
        thunk_igEnbayaContextPool_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igEnbayaContextPool_className,  /* class name */
        0x14,                                      /* instance size */
        igEnbayaContextPool_GetVTable,             /* vtable getter */
        &igEnbayaContextPool_InitFields,           /* field adder */
        0,                                         /* extra callback item */
        g_igEnbayaContextPool_callbackList  /* callback list */
    );
}
