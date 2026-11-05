/* 0x002caf90 igCharList_Register: registers class igCharList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igCharList_GetVTable[];
extern char thunk_igCharList_GetMetaObject[];
extern char s_igCharList_className_004f8658[];
extern char g_igCharList_metaObject_00586898[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002cb010(void);  /* code at 0x2cb010, passed by address (was DAT_2cb010; docs/engine/function-inventory.md) */
void igCharList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCharList_metaObject_00586898,  /* published MetaObject slot */
        igDataList_Register,               /* base class registrar */
        igDataList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igCharList_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        s_igCharList_className_004f8658,   /* class name */
        0x14,                              /* instance size */
        igCharList_GetVTable,              /* vtable getter */
        FUN_002cb010,                  /* field adder */
        0,                                 /* extra callback item */
        0                                  /* callback list */
    );
}
