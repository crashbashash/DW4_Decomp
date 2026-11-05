/* 0x001890e0 igExtendByVecFunctionList_Register: registers class igExtendByVecFunctionList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igExtendByVecFunctionList_GetVTable[];
extern char thunk_igExtendByVecFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char s_igExtendByVecFunctionList_className_004e0bb0[];
extern char g_igExtendByVecFunctionList_metaObject_00561040[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igExtendByVecFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igExtendByVecFunctionList_metaObject_00561040, /* published MetaObject slot */
        igDataList_Register,                             /* base class registrar */
        igDataList_GetPublishedMetaObject,               /* base class MetaObject accessor */
        thunk_igExtendByVecFunctionList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igExtendByVecFunctionList_className_004e0bb0,  /* class name */
        0x14,                                            /* instance size */
        igExtendByVecFunctionList_GetVTable,             /* vtable getter */
        0,                                               /* field adder */
        0,                                               /* extra callback item */
        0                                                /* callback list */
    );
}
