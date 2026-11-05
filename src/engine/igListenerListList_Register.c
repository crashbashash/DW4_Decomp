/* 0x002270c0 igListenerListList_Register: registers class igListenerListList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igListenerListList_GetVTable[];
extern char thunk_igListenerListList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igListenerListList_callbackList_00497d20[];
extern char s_igListenerListList_className_004e7bb0[];
extern char g_igListenerListList_metaObject_0056d928[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();

void igListenerListList_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igListenerListList_metaObject_0056d928, /* published MetaObject slot */
        igObjectList_Register,                    /* base class registrar */
        igObjectList_GetPublishedMetaObject,      /* base class MetaObject accessor */
        thunk_igListenerListList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igListenerListList_className_004e7bb0,  /* class name */
        0x14,                                     /* instance size */
        igListenerListList_GetVTable,             /* vtable getter */
        0,                                        /* field adder */
        0,                                        /* extra callback item */
        g_igListenerListList_callbackList_00497d20  /* callback list */
    );
}
