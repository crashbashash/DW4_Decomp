/* 0x00197a20 igRenderPackagePool_Register: registers class igRenderPackagePool with the object system, derived from igObjectPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectPool_Register[];
extern char igRenderPackagePool_GetVTable[];
extern char thunk_igRenderPackagePool_GetMetaObject[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char g_igRenderPackagePool_callbackList[];
extern char igRenderPackagePool_className[];
extern char g_igRenderPackagePool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igRenderPackagePool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRenderPackagePool_metaObject,    /* published MetaObject slot */
        igObjectPool_Register,                        /* base class registrar */
        igObjectPool_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igRenderPackagePool_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        igRenderPackagePool_className,     /* class name */
        0x20,                                         /* instance size */
        igRenderPackagePool_GetVTable,                /* vtable getter */
        0,                                            /* field adder */
        0,                                            /* extra callback item */
        g_igRenderPackagePool_callbackList   /* callback list */
    );
}
