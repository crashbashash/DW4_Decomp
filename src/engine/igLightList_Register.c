/* 0x001366d0 igLightList_Register: registers class igLightList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igLightList_GetVTable[];
extern char thunk_igLightList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igLightList_callbackList[];
extern char igLightList_className[];
extern char g_igLightList_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();

void igLightList_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLightList_metaObject,   /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igLightList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igLightList_className,    /* class name */
        0x14,                                /* instance size */
        igLightList_GetVTable,               /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igLightList_callbackList  /* callback list */
    );
}
