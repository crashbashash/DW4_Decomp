/* 0x0023a660 igCollisionCellList_Register: registers class igCollisionCellList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igCollisionCellList_GetVTable[];
extern char thunk_igCollisionCellList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igCollisionCellList_callbackList_00498580[];
extern char s_igCollisionCellList_className_004ea0f0[];
extern char g_igCollisionCellList_metaObject_0056ddc0[];
int GpFlag_SetOnce_002393f0();
int igMetaObject_RegisterClass();

void igCollisionCellList_Register(void) {
    GpFlag_SetOnce_002393f0();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCollisionCellList_metaObject_0056ddc0, /* published MetaObject slot */
        igObjectList_Register,                     /* base class registrar */
        igObjectList_GetPublishedMetaObject,       /* base class MetaObject accessor */
        thunk_igCollisionCellList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igCollisionCellList_className_004ea0f0,  /* class name */
        0x14,                                      /* instance size */
        igCollisionCellList_GetVTable,             /* vtable getter */
        0,                                         /* field adder */
        0,                                         /* extra callback item */
        g_igCollisionCellList_callbackList_00498580  /* callback list */
    );
}
