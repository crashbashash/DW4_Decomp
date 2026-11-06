/* 0x002bfe50 igMemoryPoolInfoList_Register: registers class igMemoryPoolInfoList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igMemoryPoolInfoList_GetVTable[];
extern char thunk_igMemoryPoolInfoList_GetMetaObject[];
extern char g_igMemoryPoolInfoList_callbackList[];
extern char igMemoryPoolInfoList_className[];
extern char g_igMemoryPoolInfoList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igMemoryPoolInfoList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMemoryPoolInfoList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                      /* base class registrar */
        igObjectList_GetPublishedMetaObject,        /* base class MetaObject accessor */
        thunk_igMemoryPoolInfoList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igMemoryPoolInfoList_className,  /* class name */
        0x14,                                       /* instance size */
        igMemoryPoolInfoList_GetVTable,             /* vtable getter */
        0,                                          /* field adder */
        0,                                          /* extra callback item */
        g_igMemoryPoolInfoList_callbackList  /* callback list */
    );
}
