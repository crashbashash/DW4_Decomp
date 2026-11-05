/* 0x00231ac0 igMessageFilterList_Register: registers class igMessageFilterList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igMessageFilterList_GetVTable[];
extern char thunk_igMessageFilterList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igMessageFilterList_callbackList_00497fe0[];
extern char s_igMessageFilterList_className_004e8480[];
extern char g_igMessageFilterList_metaObject_0056daf0[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();

void igMessageFilterList_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMessageFilterList_metaObject_0056daf0, /* published MetaObject slot */
        igObjectList_Register,                     /* base class registrar */
        igObjectList_GetPublishedMetaObject,       /* base class MetaObject accessor */
        thunk_igMessageFilterList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igMessageFilterList_className_004e8480,  /* class name */
        0x14,                                      /* instance size */
        igMessageFilterList_GetVTable,             /* vtable getter */
        0,                                         /* field adder */
        0,                                         /* extra callback item */
        g_igMessageFilterList_callbackList_00497fe0  /* callback list */
    );
}
