/* 0x0019a660 igLightStateAttrPool_Register: registers class igLightStateAttrPool with the object system, derived from igObjectPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject_00197aa0[];
extern char igLightStateAttrPool_GetVTable[];
extern char thunk_igLightStateAttrPool_GetMetaObject[];
extern char g_igLightStateAttrPool_callbackList_0048b750[];
extern char s_igLightStateAttrPool_className_004e1dd0[];
extern char g_igLightStateAttrPool_metaObject_005615c0[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igLightStateAttrPool_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLightStateAttrPool_metaObject_005615c0,   /* published MetaObject slot */
        igObjectPool_Register,                        /* base class registrar */
        igObjectPool_GetPublishedMetaObject_00197aa0, /* base class MetaObject accessor */
        thunk_igLightStateAttrPool_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igLightStateAttrPool_className_004e1dd0,    /* class name */
        0x20,                                         /* instance size */
        igLightStateAttrPool_GetVTable,               /* vtable getter */
        0,                                            /* field adder */
        0,                                            /* extra callback item */
        g_igLightStateAttrPool_callbackList_0048b750  /* callback list */
    );
}
