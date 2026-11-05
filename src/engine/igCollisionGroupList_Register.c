/* 0x00239b30 igCollisionGroupList_Register: registers class igCollisionGroupList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igCollisionGroupList_GetVTable[];
extern char thunk_igCollisionGroupList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igCollisionGroupList_callbackList_004983a8[];
extern char s_igCollisionGroupList_className_004e9f40[];
extern char g_igCollisionGroupList_metaObject_0056dcd8[];
int GpFlag_SetOnce_002393f0();
int igMetaObject_RegisterClass();

void igCollisionGroupList_Register(void) {
    GpFlag_SetOnce_002393f0();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCollisionGroupList_metaObject_0056dcd8, /* published MetaObject slot */
        igObjectList_Register,                      /* base class registrar */
        igObjectList_GetPublishedMetaObject,        /* base class MetaObject accessor */
        thunk_igCollisionGroupList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igCollisionGroupList_className_004e9f40,  /* class name */
        0x14,                                       /* instance size */
        igCollisionGroupList_GetVTable,             /* vtable getter */
        0,                                          /* field adder */
        0,                                          /* extra callback item */
        g_igCollisionGroupList_callbackList_004983a8  /* callback list */
    );
}
