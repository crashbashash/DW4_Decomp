/* 0x00199c50 igTextureMatrixAttrPool_Register: registers class igTextureMatrixAttrPool with the object system, derived from igObjectPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject_00197aa0[];
extern char igTextureMatrixAttrPool_GetVTable[];
extern char thunk_igTextureMatrixAttrPool_GetMetaObject[];
extern char g_igTextureMatrixAttrPool_callbackList_0048b718[];
extern char s_igTextureMatrixAttrPool_className_004e1d00[];
extern char g_igTextureMatrixAttrPool_metaObject_00561588[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igTextureMatrixAttrPool_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTextureMatrixAttrPool_metaObject_00561588, /* published MetaObject slot */
        igObjectPool_Register,                         /* base class registrar */
        igObjectPool_GetPublishedMetaObject_00197aa0,  /* base class MetaObject accessor */
        thunk_igTextureMatrixAttrPool_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igTextureMatrixAttrPool_className_004e1d00,  /* class name */
        0x20,                                          /* instance size */
        igTextureMatrixAttrPool_GetVTable,             /* vtable getter */
        0,                                             /* field adder */
        0,                                             /* extra callback item */
        g_igTextureMatrixAttrPool_callbackList_0048b718  /* callback list */
    );
}
