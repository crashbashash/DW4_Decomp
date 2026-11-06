/* 0x002c0370 igMemoryPoolContextInfo_Register: registers class igMemoryPoolContextInfo with the object system, derived from igInfo.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInfo_GetPublishedMetaObject[];
extern char igMemoryPoolContextInfo_GetVTable[];
extern char thunk_igMemoryPoolContextInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char g_igMemoryPoolContextInfo_callbackList[];
extern char igMemoryPoolContextInfo_className[];
extern char g_igMemoryPoolContextInfo_metaObject_00585e88[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igMemoryPoolContextInfo_InitFields();

void igMemoryPoolContextInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMemoryPoolContextInfo_metaObject_00585e88, /* published MetaObject slot */
        igInfo_Register,                               /* base class registrar */
        igInfo_GetPublishedMetaObject,        /* base class MetaObject accessor */
        thunk_igMemoryPoolContextInfo_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igMemoryPoolContextInfo_className,  /* class name */
        0x18,                                          /* instance size */
        igMemoryPoolContextInfo_GetVTable,             /* vtable getter */
        &igMemoryPoolContextInfo_InitFields,           /* field adder */
        0,                                             /* extra callback item */
        g_igMemoryPoolContextInfo_callbackList  /* callback list */
    );
}
