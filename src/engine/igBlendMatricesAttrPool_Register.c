/* 0x00199ae0 igBlendMatricesAttrPool_Register: registers class igBlendMatricesAttrPool with the object system, derived from igObjectPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject_00197aa0[];
extern char igBlendMatricesAttrPool_GetVTable[];
extern char thunk_igBlendMatricesAttrPool_GetMetaObject[];
extern char g_igBlendMatricesAttrPool_callbackList_0048b710[];
extern char s_igBlendMatricesAttrPool_className_004e1ce0[];
extern char g_igBlendMatricesAttrPool_metaObject_00561580[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igBlendMatricesAttrPool_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBlendMatricesAttrPool_metaObject_00561580, /* published MetaObject slot */
        igObjectPool_Register,                         /* base class registrar */
        igObjectPool_GetPublishedMetaObject_00197aa0,  /* base class MetaObject accessor */
        thunk_igBlendMatricesAttrPool_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igBlendMatricesAttrPool_className_004e1ce0,  /* class name */
        0x20,                                          /* instance size */
        igBlendMatricesAttrPool_GetVTable,             /* vtable getter */
        0,                                             /* field adder */
        0,                                             /* extra callback item */
        g_igBlendMatricesAttrPool_callbackList_0048b710  /* callback list */
    );
}
