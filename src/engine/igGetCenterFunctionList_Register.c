/* 0x00188a00 igGetCenterFunctionList_Register: registers class igGetCenterFunctionList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igGetCenterFunctionList_GetVTable[];
extern char thunk_igGetCenterFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char s_igGetCenterFunctionList_className_004e0b10[];
extern char g_igGetCenterFunctionList_metaObject_00561018[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igGetCenterFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGetCenterFunctionList_metaObject_00561018, /* published MetaObject slot */
        igDataList_Register,                           /* base class registrar */
        igDataList_GetPublishedMetaObject,             /* base class MetaObject accessor */
        thunk_igGetCenterFunctionList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igGetCenterFunctionList_className_004e0b10,  /* class name */
        0x14,                                          /* instance size */
        igGetCenterFunctionList_GetVTable,             /* vtable getter */
        0,                                             /* field adder */
        0,                                             /* extra callback item */
        0                                              /* callback list */
    );
}
