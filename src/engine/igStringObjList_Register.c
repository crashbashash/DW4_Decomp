/* 0x002b9480 igStringObjList_Register: registers class igStringObjList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igStringObjList_GetVTable[];
extern char thunk_igStringObjList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igStringObjList_callbackList[];
extern char igStringObjList_className[];
extern char g_igStringObjList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igStringObjList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStringObjList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                 /* base class registrar */
        igObjectList_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igStringObjList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igStringObjList_className,  /* class name */
        0x14,                                  /* instance size */
        igStringObjList_GetVTable,             /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        g_igStringObjList_callbackList  /* callback list */
    );
}
