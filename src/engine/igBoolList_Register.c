/* 0x002cb200 igBoolList_Register: registers class igBoolList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igBoolList_GetVTable[];
extern char thunk_igBoolList_GetMetaObject[];
extern char s_igBoolList_className_004f8668[];
extern char g_igBoolList_metaObject_005868a8[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002cb280(void);  /* code at 0x2cb280, passed by address (was DAT_2cb280; docs/engine/function-inventory.md) */
void igBoolList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBoolList_metaObject_005868a8,  /* published MetaObject slot */
        igDataList_Register,               /* base class registrar */
        igDataList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igBoolList_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        s_igBoolList_className_004f8668,   /* class name */
        0x14,                              /* instance size */
        igBoolList_GetVTable,              /* vtable getter */
        FUN_002cb280,                  /* field adder */
        0,                                 /* extra callback item */
        0                                  /* callback list */
    );
}
