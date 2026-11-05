/* 0x002c0100 igMemoryPoolInfo_Register: registers class igMemoryPoolInfo with the object system, derived from igInfo.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInfo_GetPublishedMetaObject_00131c50[];
extern char igMemoryPoolInfo_GetVTable[];
extern char thunk_igMemoryPoolInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char s_igMemoryPoolInfo_className_004f69e0[];
extern char g_igMemoryPoolInfo_metaObject_00585e00[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igMemoryPoolInfo_InitFields();

void igMemoryPoolInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMemoryPoolInfo_metaObject_00585e00, /* published MetaObject slot */
        igInfo_Register,                        /* base class registrar */
        igInfo_GetPublishedMetaObject_00131c50, /* base class MetaObject accessor */
        thunk_igMemoryPoolInfo_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igMemoryPoolInfo_className_004f69e0,  /* class name */
        0x54,                                   /* instance size */
        igMemoryPoolInfo_GetVTable,             /* vtable getter */
        &igMemoryPoolInfo_InitFields,           /* field adder */
        0,                                      /* extra callback item */
        0                                       /* callback list */
    );
}
