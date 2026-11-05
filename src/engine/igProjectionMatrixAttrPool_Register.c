/* 0x0019a210 igProjectionMatrixAttrPool_Register: registers class igProjectionMatrixAttrPool with the object system, derived from igObjectPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject_00197aa0[];
extern char igProjectionMatrixAttrPool_GetVTable[];
extern char thunk_igProjectionMatrixAttrPool_GetMetaObject[];
extern char g_igProjectionMatrixAttrPool_callbackList_0048b738[];
extern char s_igProjectionMatrixAttrPool_className_004e1d80[];
extern char g_igProjectionMatrixAttrPool_metaObject_005615a8[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igProjectionMatrixAttrPool_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igProjectionMatrixAttrPool_metaObject_005615a8, /* published MetaObject slot */
        igObjectPool_Register,                            /* base class registrar */
        igObjectPool_GetPublishedMetaObject_00197aa0,     /* base class MetaObject accessor */
        thunk_igProjectionMatrixAttrPool_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igProjectionMatrixAttrPool_className_004e1d80,  /* class name */
        0x20,                                             /* instance size */
        igProjectionMatrixAttrPool_GetVTable,             /* vtable getter */
        0,                                                /* field adder */
        0,                                                /* extra callback item */
        g_igProjectionMatrixAttrPool_callbackList_0048b738  /* callback list */
    );
}
