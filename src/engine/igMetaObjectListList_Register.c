/* 0x002c8d90 igMetaObjectListList_Register: registers class igMetaObjectListList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igMetaObjectListList_GetVTable[];
extern char thunk_igMetaObjectListList_GetMetaObject[];
extern char g_igMetaObjectListList_callbackList[];
extern char igMetaObjectListList_className[];
extern char g_igMetaObjectListList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igMetaObjectListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMetaObjectListList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                      /* base class registrar */
        igObjectList_GetPublishedMetaObject,        /* base class MetaObject accessor */
        thunk_igMetaObjectListList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igMetaObjectListList_className,  /* class name */
        0x14,                                       /* instance size */
        igMetaObjectListList_GetVTable,             /* vtable getter */
        0,                                          /* field adder */
        0,                                          /* extra callback item */
        g_igMetaObjectListList_callbackList  /* callback list */
    );
}
