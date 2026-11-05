/* 0x002c8a70 igIntListList_Register: registers class igIntListList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igIntListList_GetVTable[];
extern char thunk_igIntListList_GetMetaObject[];
extern char g_igIntListList_callbackList_004c13d0[];
extern char s_igIntListList_className_004f8498[];
extern char g_igIntListList_metaObject_005867b8[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igIntListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIntListList_metaObject_005867b8, /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igIntListList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igIntListList_className_004f8498,  /* class name */
        0x14,                                /* instance size */
        igIntListList_GetVTable,             /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igIntListList_callbackList_004c13d0  /* callback list */
    );
}
