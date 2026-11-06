/* 0x002271e0 igListenerList_Register: registers class igListenerList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igListenerList_GetVTable[];
extern char thunk_igListenerList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igListenerList_callbackList[];
extern char igListenerList_className[];
extern char g_igListenerList_metaObject[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();

void igListenerList_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                    /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igListenerList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                /* base class registrar */
        igObjectList_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igListenerList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igListenerList_className,  /* class name */
        0x14,                                 /* instance size */
        igListenerList_GetVTable,             /* vtable getter */
        0,                                    /* field adder */
        0,                                    /* extra callback item */
        g_igListenerList_callbackList  /* callback list */
    );
}
