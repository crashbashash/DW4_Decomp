/* 0x002c1660 igMediaList_Register: registers class igMediaList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igMediaList_GetVTable[];
extern char thunk_igMediaList_GetMetaObject[];
extern char g_igMediaList_callbackList[];
extern char igMediaList_className[];
extern char g_igMediaList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igMediaList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMediaList_metaObject,   /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igMediaList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igMediaList_className,    /* class name */
        0x14,                                /* instance size */
        igMediaList_GetVTable,               /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igMediaList_callbackList  /* callback list */
    );
}
