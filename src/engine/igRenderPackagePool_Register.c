/* 0x00197a20 igRenderPackagePool_Register: registers class igRenderPackagePool with the object system, derived from igObjectPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectPool_Register[];
extern char igRenderPackagePool_GetVTable[];
extern char thunk_igRenderPackagePool_GetMetaObject[];
extern char igObjectPool_GetPublishedMetaObject_00197aa0[];
extern char g_igRenderPackagePool_callbackList_0048b4b8[];
extern char s_igRenderPackagePool_className_004e19c0[];
extern char g_igRenderPackagePool_metaObject_00561448[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igRenderPackagePool_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRenderPackagePool_metaObject_00561448,    /* published MetaObject slot */
        igObjectPool_Register,                        /* base class registrar */
        igObjectPool_GetPublishedMetaObject_00197aa0, /* base class MetaObject accessor */
        thunk_igRenderPackagePool_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        s_igRenderPackagePool_className_004e19c0,     /* class name */
        0x20,                                         /* instance size */
        igRenderPackagePool_GetVTable,                /* vtable getter */
        0,                                            /* field adder */
        0,                                            /* extra callback item */
        g_igRenderPackagePool_callbackList_0048b4b8   /* callback list */
    );
}
