/* 0x00231f50 igFilterMessageDispatcher_Register: registers class igFilterMessageDispatcher with the object system, derived from igMessageDispatcher.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igFilterMessageDispatcher_GetVTable[];
extern char thunk_igFilterMessageDispatcher_GetMetaObject[];
extern char igMessageDispatcher_GetPublishedMetaObject_00231fe0[];
extern char igMessageDispatcher_Register[];
extern char g_igFilterMessageDispatcher_callbackList_00498018[];
extern char s_igFilterMessageDispatcher_className_004e84d0[];
extern char g_igFilterMessageDispatcher_metaObject_0056db10[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();
int igFilterMessageDispatcher_InitFields();

void igFilterMessageDispatcher_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        0,                                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFilterMessageDispatcher_metaObject_0056db10,     /* published MetaObject slot */
        igMessageDispatcher_Register,                        /* base class registrar */
        igMessageDispatcher_GetPublishedMetaObject_00231fe0, /* base class MetaObject accessor */
        thunk_igFilterMessageDispatcher_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igFilterMessageDispatcher_className_004e84d0,      /* class name */
        0x10,                                                /* instance size */
        igFilterMessageDispatcher_GetVTable,                 /* vtable getter */
        &igFilterMessageDispatcher_InitFields,               /* field adder */
        0,                                                   /* extra callback item */
        g_igFilterMessageDispatcher_callbackList_00498018    /* callback list */
    );
}
