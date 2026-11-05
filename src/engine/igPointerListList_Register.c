/* 0x002c90b0 igPointerListList_Register: registers class igPointerListList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igPointerListList_GetVTable[];
extern char thunk_igPointerListList_GetMetaObject[];
extern char g_igPointerListList_callbackList_004c13f0[];
extern char s_igPointerListList_className_004f8500[];
extern char g_igPointerListList_metaObject_005867d8[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igPointerListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPointerListList_metaObject_005867d8, /* published MetaObject slot */
        igObjectList_Register,                   /* base class registrar */
        igObjectList_GetPublishedMetaObject,     /* base class MetaObject accessor */
        thunk_igPointerListList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igPointerListList_className_004f8500,  /* class name */
        0x14,                                    /* instance size */
        igPointerListList_GetVTable,             /* vtable getter */
        0,                                       /* field adder */
        0,                                       /* extra callback item */
        g_igPointerListList_callbackList_004c13f0  /* callback list */
    );
}
