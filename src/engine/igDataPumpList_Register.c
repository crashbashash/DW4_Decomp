/* 0x001e54b0 igDataPumpList_Register: registers class igDataPumpList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igDataPumpList_GetVTable[];
extern char thunk_igDataPumpList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igDataPumpList_callbackList[];
extern char igDataPumpList_className[];
extern char g_igDataPumpList_metaObject[];
int GpFlag_SetOnce_001e3ff0();
int igMetaObject_RegisterClass();

void igDataPumpList_Register(void) {
    GpFlag_SetOnce_001e3ff0();
    igMetaObject_RegisterClass(
        0,                                    /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDataPumpList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                /* base class registrar */
        igObjectList_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igDataPumpList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igDataPumpList_className,  /* class name */
        0x14,                                 /* instance size */
        igDataPumpList_GetVTable,             /* vtable getter */
        0,                                    /* field adder */
        0,                                    /* extra callback item */
        g_igDataPumpList_callbackList  /* callback list */
    );
}
