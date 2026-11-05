/* 0x00189920 igIntersectionFunctionList_Register: registers class igIntersectionFunctionList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igIntersectionFunctionList_GetVTable[];
extern char thunk_igIntersectionFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char s_igIntersectionFunctionList_className_004e0c70[];
extern char g_igIntersectionFunctionList_metaObject_00561070[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igIntersectionFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                                /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIntersectionFunctionList_metaObject_00561070, /* published MetaObject slot */
        igDataList_Register,                              /* base class registrar */
        igDataList_GetPublishedMetaObject,                /* base class MetaObject accessor */
        thunk_igIntersectionFunctionList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igIntersectionFunctionList_className_004e0c70,  /* class name */
        0x14,                                             /* instance size */
        igIntersectionFunctionList_GetVTable,             /* vtable getter */
        0,                                                /* field adder */
        0,                                                /* extra callback item */
        0                                                 /* callback list */
    );
}
