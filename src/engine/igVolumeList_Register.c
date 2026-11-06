/* 0x00186d30 igVolumeList_Register: registers class igVolumeList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igVolumeList_GetVTable[];
extern char thunk_igVolumeList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igVolumeList_callbackList[];
extern char igVolumeList_className[];
extern char g_igVolumeList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igVolumeList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVolumeList_metaObject,  /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igVolumeList_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        igVolumeList_className,   /* class name */
        0x14,                                /* instance size */
        igVolumeList_GetVTable,              /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igVolumeList_callbackList  /* callback list */
    );
}
