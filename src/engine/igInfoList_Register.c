/* 0x002c3530 igInfoList_Register: registers class igInfoList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igInfoList_GetVTable[];
extern char thunk_igInfoList_GetMetaObject[];
extern char g_igInfoList_callbackList[];
extern char igInfoList_className[];
extern char g_igInfoList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igInfoList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igInfoList_metaObject,    /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igInfoList_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        igInfoList_className,     /* class name */
        0x14,                                /* instance size */
        igInfoList_GetVTable,                /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igInfoList_callbackList   /* callback list */
    );
}
