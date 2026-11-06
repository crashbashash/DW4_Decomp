/* 0x0019a380 igTimeAttrPool_Register: registers class igTimeAttrPool with the object system, derived from igObjectPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igTimeAttrPool_GetVTable[];
extern char thunk_igTimeAttrPool_GetMetaObject[];
extern char g_igTimeAttrPool_callbackList[];
extern char igTimeAttrPool_className[];
extern char g_igTimeAttrPool_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igTimeAttrPool_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTimeAttrPool_metaObject,         /* published MetaObject slot */
        igObjectPool_Register,                        /* base class registrar */
        igObjectPool_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igTimeAttrPool_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        igTimeAttrPool_className,          /* class name */
        0x20,                                         /* instance size */
        igTimeAttrPool_GetVTable,                     /* vtable getter */
        0,                                            /* field adder */
        0,                                            /* extra callback item */
        g_igTimeAttrPool_callbackList        /* callback list */
    );
}
