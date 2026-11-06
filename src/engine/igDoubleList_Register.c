/* 0x002c9490 igDoubleList_Register: registers class igDoubleList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igDoubleList_GetVTable[];
extern char thunk_igDoubleList_GetMetaObject[];
extern char igDoubleList_className[];
extern char g_igDoubleList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002c9510(void);  /* code at 0x2c9510, passed by address (was DAT_2c9510; docs/engine/function-inventory.md) */
void igDoubleList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                  /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDoubleList_metaObject, /* published MetaObject slot */
        igDataList_Register,                /* base class registrar */
        igDataList_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igDoubleList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igDoubleList_className,  /* class name */
        0x14,                               /* instance size */
        igDoubleList_GetVTable,             /* vtable getter */
        FUN_002c9510,                   /* field adder */
        0,                                  /* extra callback item */
        0                                   /* callback list */
    );
}
