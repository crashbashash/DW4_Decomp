/* 0x001881a0 igRayList_Register: registers class igRayList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igRayList_GetVTable[];
extern char thunk_igRayList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igRayList_callbackList[];
extern char igRayList_className[];
extern char g_igRayList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igRayList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRayList_metaObject,     /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igRayList_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igRayList_className,      /* class name */
        0x14,                                /* instance size */
        igRayList_GetVTable,                 /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igRayList_callbackList    /* callback list */
    );
}
