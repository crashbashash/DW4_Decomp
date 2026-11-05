/* 0x002cb5e0 igContextExtInfoList_Register: registers class igContextExtInfoList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igContextExtInfoList_GetVTable[];
extern char thunk_igContextExtInfoList_GetMetaObject[];
extern char g_igContextExtInfoList_callbackList_004c1410[];
extern char s_igContextExtInfoList_className_004f86a0[];
extern char g_igContextExtInfoList_metaObject_005868c0[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igContextExtInfoList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igContextExtInfoList_metaObject_005868c0, /* published MetaObject slot */
        igObjectList_Register,                      /* base class registrar */
        igObjectList_GetPublishedMetaObject,        /* base class MetaObject accessor */
        thunk_igContextExtInfoList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igContextExtInfoList_className_004f86a0,  /* class name */
        0x14,                                       /* instance size */
        igContextExtInfoList_GetVTable,             /* vtable getter */
        0,                                          /* field adder */
        0,                                          /* extra callback item */
        g_igContextExtInfoList_callbackList_004c1410  /* callback list */
    );
}
