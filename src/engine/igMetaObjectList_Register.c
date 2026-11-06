/* 0x002c8f40 igMetaObjectList_Register: registers class igMetaObjectList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igMetaObjectList_GetVTable[];
extern char thunk_igMetaObjectList_GetMetaObject[];
extern char g_igMetaObjectList_callbackList[];
extern char igMetaObjectList_className[];
extern char g_igMetaObjectList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igMetaObjectList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMetaObjectList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                  /* base class registrar */
        igObjectList_GetPublishedMetaObject,    /* base class MetaObject accessor */
        thunk_igMetaObjectList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igMetaObjectList_className,  /* class name */
        0x14,                                   /* instance size */
        igMetaObjectList_GetVTable,             /* vtable getter */
        0,                                      /* field adder */
        0,                                      /* extra callback item */
        g_igMetaObjectList_callbackList  /* callback list */
    );
}
