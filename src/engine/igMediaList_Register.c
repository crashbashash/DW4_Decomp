/* 0x002c1660 igMediaList_Register: registers class igMediaList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igMediaList_GetVTable[];
extern char thunk_igMediaList_GetMetaObject[];
extern char g_igMediaList_callbackList_004c0498[];
extern char s_igMediaList_className_004f6e80[];
extern char g_igMediaList_metaObject_00586018[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igMediaList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMediaList_metaObject_00586018,   /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igMediaList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igMediaList_className_004f6e80,    /* class name */
        0x14,                                /* instance size */
        igMediaList_GetVTable,               /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igMediaList_callbackList_004c0498  /* callback list */
    );
}
