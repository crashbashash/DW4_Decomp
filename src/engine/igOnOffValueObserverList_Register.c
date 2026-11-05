/* 0x0044c970 igOnOffValueObserverList_Register: registers class igOnOffValueObserverList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igOnOffValueObserverList_GetVTable[];
extern char thunk_igOnOffValueObserverList_GetMetaObject[];
extern char g_igOnOffValueObserverList_callbackList_004cffb8[];
extern char s_igOnOffValueObserverList_className_0051ddf0[];
extern char g_igOnOffValueObserverList_metaObject_0058c218[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();

void igOnOffValueObserverList_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igOnOffValueObserverList_metaObject_0058c218, /* published MetaObject slot */
        igObjectList_Register,                          /* base class registrar */
        igObjectList_GetPublishedMetaObject,            /* base class MetaObject accessor */
        thunk_igOnOffValueObserverList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igOnOffValueObserverList_className_0051ddf0,  /* class name */
        0x14,                                           /* instance size */
        igOnOffValueObserverList_GetVTable,             /* vtable getter */
        0,                                              /* field adder */
        0,                                              /* extra callback item */
        g_igOnOffValueObserverList_callbackList_004cffb8  /* callback list */
    );
}
