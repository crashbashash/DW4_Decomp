/* 0x00136130 igLightStateAttrList_Register: registers class igLightStateAttrList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igLightStateAttrList_GetVTable[];
extern char thunk_igLightStateAttrList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igLightStateAttrList_callbackList[];
extern char igLightStateAttrList_className[];
extern char g_igLightStateAttrList_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igLightStateAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLightStateAttrList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                      /* base class registrar */
        igObjectList_GetPublishedMetaObject,        /* base class MetaObject accessor */
        thunk_igLightStateAttrList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igLightStateAttrList_className,  /* class name */
        0x14,                                       /* instance size */
        igLightStateAttrList_GetVTable,             /* vtable getter */
        0,                                          /* field adder */
        0,                                          /* extra callback item */
        g_igLightStateAttrList_callbackList  /* callback list */
    );
}
