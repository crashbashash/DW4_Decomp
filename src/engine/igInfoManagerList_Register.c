/* 0x00233840 igInfoManagerList_Register: registers class igInfoManagerList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igInfoManagerList_GetVTable[];
extern char thunk_igInfoManagerList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igInfoManagerList_callbackList[];
extern char igInfoManagerList_className[];
extern char g_igInfoManagerList_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igInfoManagerList_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igInfoManagerList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                   /* base class registrar */
        igObjectList_GetPublishedMetaObject,     /* base class MetaObject accessor */
        thunk_igInfoManagerList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igInfoManagerList_className,  /* class name */
        0x14,                                    /* instance size */
        igInfoManagerList_GetVTable,             /* vtable getter */
        0,                                       /* field adder */
        0,                                       /* extra callback item */
        g_igInfoManagerList_callbackList  /* callback list */
    );
}
