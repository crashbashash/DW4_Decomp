/* 0x002c7e30 igDependencyList_Register: registers class igDependencyList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igDependencyList_GetVTable[];
extern char thunk_igDependencyList_GetMetaObject[];
extern char igDataList_Register[];
extern char s_igDependencyList_className_004f8400[];
extern char g_igDependencyList_metaObject_00586768[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002c7eb0(void);  /* code at 0x2c7eb0, passed by address (was DAT_2c7eb0; docs/engine/function-inventory.md) */
void igDependencyList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDependencyList_metaObject_00586768, /* published MetaObject slot */
        igDataList_Register,                    /* base class registrar */
        igDataList_GetPublishedMetaObject,      /* base class MetaObject accessor */
        thunk_igDependencyList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igDependencyList_className_004f8400,  /* class name */
        0x14,                                   /* instance size */
        igDependencyList_GetVTable,             /* vtable getter */
        FUN_002c7eb0,                       /* field adder */
        0,                                      /* extra callback item */
        0                                       /* callback list */
    );
}
