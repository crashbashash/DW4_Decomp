/* 0x00188f80 igContainsVecFunctionList_Register: registers class igContainsVecFunctionList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igContainsVecFunctionList_GetVTable[];
extern char thunk_igContainsVecFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char igContainsVecFunctionList_className[];
extern char g_igContainsVecFunctionList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igContainsVecFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igContainsVecFunctionList_metaObject, /* published MetaObject slot */
        igDataList_Register,                             /* base class registrar */
        igDataList_GetPublishedMetaObject,               /* base class MetaObject accessor */
        thunk_igContainsVecFunctionList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igContainsVecFunctionList_className,  /* class name */
        0x14,                                            /* instance size */
        igContainsVecFunctionList_GetVTable,             /* vtable getter */
        0,                                               /* field adder */
        0,                                               /* extra callback item */
        0                                                /* callback list */
    );
}
