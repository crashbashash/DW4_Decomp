/* 0x00226430 igMessageList_Register: registers class igMessageList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igMessageList_GetVTable[];
extern char thunk_igMessageList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igMessageList_callbackList_00497c58[];
extern char s_igMessageList_className_004e7a98[];
extern char g_igMessageList_metaObject_0056d8b8[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();

void igMessageList_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMessageList_metaObject_0056d8b8, /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igMessageList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igMessageList_className_004e7a98,  /* class name */
        0x14,                                /* instance size */
        igMessageList_GetVTable,             /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igMessageList_callbackList_00497c58  /* callback list */
    );
}
