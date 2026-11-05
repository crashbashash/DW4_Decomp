/* 0x002c8900 igObjectListList_Register: registers class igObjectListList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igObjectListList_GetVTable[];
extern char thunk_igObjectListList_GetMetaObject[];
extern char g_igObjectListList_callbackList_004c13c8[];
extern char s_igObjectListList_className_004f8480[];
extern char g_igObjectListList_metaObject_005867b0[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igObjectListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igObjectListList_metaObject_005867b0, /* published MetaObject slot */
        igObjectList_Register,                  /* base class registrar */
        igObjectList_GetPublishedMetaObject,    /* base class MetaObject accessor */
        thunk_igObjectListList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igObjectListList_className_004f8480,  /* class name */
        0x14,                                   /* instance size */
        igObjectListList_GetVTable,             /* vtable getter */
        0,                                      /* field adder */
        0,                                      /* extra callback item */
        g_igObjectListList_callbackList_004c13c8  /* callback list */
    );
}
