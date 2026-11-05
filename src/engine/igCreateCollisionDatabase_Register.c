/* 0x002395c0 igCreateCollisionDatabase_Register: registers class igCreateCollisionDatabase with the object system, derived from igOptBase.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igOptBase_GetPublishedMetaObject_00225a30[];
extern char igOptBase_Register[];
extern char igCreateCollisionDatabase_GetVTable[];
extern char thunk_igCreateCollisionDatabase_GetMetaObject[];
extern char g_igCreateCollisionDatabase_callbackList_004982e8[];
extern char s_igCreateCollisionDatabase_className_004e9eb0[];
extern char g_igCreateCollisionDatabase_metaObject_0056dc88[];
int GpFlag_SetOnce_002393f0();
int igMetaObject_RegisterClass();
int igCreateCollisionDatabase_InitFields();

void igCreateCollisionDatabase_Register(void) {
    GpFlag_SetOnce_002393f0();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCreateCollisionDatabase_metaObject_0056dc88, /* published MetaObject slot */
        igOptBase_Register,                              /* base class registrar */
        igOptBase_GetPublishedMetaObject_00225a30,       /* base class MetaObject accessor */
        thunk_igCreateCollisionDatabase_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igCreateCollisionDatabase_className_004e9eb0,  /* class name */
        0x44,                                            /* instance size */
        igCreateCollisionDatabase_GetVTable,             /* vtable getter */
        &igCreateCollisionDatabase_InitFields,           /* field adder */
        0,                                               /* extra callback item */
        g_igCreateCollisionDatabase_callbackList_004982e8  /* callback list */
    );
}
