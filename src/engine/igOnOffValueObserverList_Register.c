/* 0x0044c970 igOnOffValueObserverList_Register: registers class igOnOffValueObserverList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igOnOffValueObserverList_GetVTable[];
extern char thunk_igOnOffValueObserverList_GetMetaObject[];
extern char g_igOnOffValueObserverList_callbackList[];
extern char igOnOffValueObserverList_className[];
extern char g_igOnOffValueObserverList_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igOnOffValueObserverList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igOnOffValueObserverList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                          /* base class registrar */
        igObjectList_GetPublishedMetaObject,            /* base class MetaObject accessor */
        thunk_igOnOffValueObserverList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igOnOffValueObserverList_className,  /* class name */
        0x14,                                           /* instance size */
        igOnOffValueObserverList_GetVTable,             /* vtable getter */
        0,                                              /* field adder */
        0,                                              /* extra callback item */
        g_igOnOffValueObserverList_callbackList  /* callback list */
    );
}
