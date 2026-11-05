/* 0x00188cc0 igEmptyFunctionList_Register: registers class igEmptyFunctionList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igEmptyFunctionList_GetVTable[];
extern char thunk_igEmptyFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char s_igEmptyFunctionList_className_004e0b50[];
extern char g_igEmptyFunctionList_metaObject_00561028[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igEmptyFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igEmptyFunctionList_metaObject_00561028, /* published MetaObject slot */
        igDataList_Register,                       /* base class registrar */
        igDataList_GetPublishedMetaObject,         /* base class MetaObject accessor */
        thunk_igEmptyFunctionList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igEmptyFunctionList_className_004e0b50,  /* class name */
        0x14,                                      /* instance size */
        igEmptyFunctionList_GetVTable,             /* vtable getter */
        0,                                         /* field adder */
        0,                                         /* extra callback item */
        0                                          /* callback list */
    );
}
