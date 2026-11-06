/* 0x002c8900 igObjectListList_Register: registers class igObjectListList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igObjectListList_GetVTable[];
extern char thunk_igObjectListList_GetMetaObject[];
extern char g_igObjectListList_callbackList[];
extern char igObjectListList_className[];
extern char g_igObjectListList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igObjectListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igObjectListList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                  /* base class registrar */
        igObjectList_GetPublishedMetaObject,    /* base class MetaObject accessor */
        thunk_igObjectListList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igObjectListList_className,  /* class name */
        0x14,                                   /* instance size */
        igObjectListList_GetVTable,             /* vtable getter */
        0,                                      /* field adder */
        0,                                      /* extra callback item */
        g_igObjectListList_callbackList  /* callback list */
    );
}
