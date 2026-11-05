/* 0x0018a5e0 igAABoxList_Register: registers class igAABoxList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igAABoxList_GetVTable[];
extern char thunk_igAABoxList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAABoxList_callbackList_0048ae50[];
extern char s_igAABoxList_className_004e0cf8[];
extern char g_igAABoxList_metaObject_005610d8[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igAABoxList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAABoxList_metaObject_005610d8,   /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igAABoxList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igAABoxList_className_004e0cf8,    /* class name */
        0x14,                                /* instance size */
        igAABoxList_GetVTable,               /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igAABoxList_callbackList_0048ae50  /* callback list */
    );
}
