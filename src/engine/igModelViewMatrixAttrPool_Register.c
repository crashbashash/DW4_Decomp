/* 0x0019a4f0 igModelViewMatrixAttrPool_Register: registers class igModelViewMatrixAttrPool with the object system, derived from igObjectPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igModelViewMatrixAttrPool_GetVTable[];
extern char thunk_igModelViewMatrixAttrPool_GetMetaObject[];
extern char g_igModelViewMatrixAttrPool_callbackList[];
extern char igModelViewMatrixAttrPool_className[];
extern char g_igModelViewMatrixAttrPool_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igModelViewMatrixAttrPool_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igModelViewMatrixAttrPool_metaObject, /* published MetaObject slot */
        igObjectPool_Register,                           /* base class registrar */
        igObjectPool_GetPublishedMetaObject,    /* base class MetaObject accessor */
        thunk_igModelViewMatrixAttrPool_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igModelViewMatrixAttrPool_className,  /* class name */
        0x20,                                            /* instance size */
        igModelViewMatrixAttrPool_GetVTable,             /* vtable getter */
        0,                                               /* field adder */
        0,                                               /* extra callback item */
        g_igModelViewMatrixAttrPool_callbackList  /* callback list */
    );
}
