/* 0x00189500 igRayIntersectionFunctionList_Register: registers class igRayIntersectionFunctionList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igRayIntersectionFunctionList_GetVTable[];
extern char thunk_igRayIntersectionFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char igRayIntersectionFunctionList_className[];
extern char g_igRayIntersectionFunctionList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igRayIntersectionFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRayIntersectionFunctionList_metaObject, /* published MetaObject slot */
        igDataList_Register,                                 /* base class registrar */
        igDataList_GetPublishedMetaObject,                   /* base class MetaObject accessor */
        thunk_igRayIntersectionFunctionList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igRayIntersectionFunctionList_className,  /* class name */
        0x14,                                                /* instance size */
        igRayIntersectionFunctionList_GetVTable,             /* vtable getter */
        0,                                                   /* field adder */
        0,                                                   /* extra callback item */
        0                                                    /* callback list */
    );
}
