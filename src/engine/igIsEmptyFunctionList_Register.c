/* 0x00188b60 igIsEmptyFunctionList_Register: registers class igIsEmptyFunctionList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igIsEmptyFunctionList_GetVTable[];
extern char thunk_igIsEmptyFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char s_igIsEmptyFunctionList_className_004e0b30[];
extern char g_igIsEmptyFunctionList_metaObject_00561020[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igIsEmptyFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIsEmptyFunctionList_metaObject_00561020, /* published MetaObject slot */
        igDataList_Register,                         /* base class registrar */
        igDataList_GetPublishedMetaObject,           /* base class MetaObject accessor */
        thunk_igIsEmptyFunctionList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igIsEmptyFunctionList_className_004e0b30,  /* class name */
        0x14,                                        /* instance size */
        igIsEmptyFunctionList_GetVTable,             /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        0                                            /* callback list */
    );
}
