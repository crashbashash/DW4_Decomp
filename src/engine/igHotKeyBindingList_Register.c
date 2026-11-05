/* 0x0044dba0 igHotKeyBindingList_Register: registers class igHotKeyBindingList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igHotKeyBindingList_GetVTable[];
extern char thunk_igHotKeyBindingList_GetMetaObject[];
extern char g_igHotKeyBindingList_callbackList_004d0128[];
extern char s_igHotKeyBindingList_className_0051df50[];
extern char g_igHotKeyBindingList_metaObject_0058c2b8[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();

void igHotKeyBindingList_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igHotKeyBindingList_metaObject_0058c2b8, /* published MetaObject slot */
        igObjectList_Register,                     /* base class registrar */
        igObjectList_GetPublishedMetaObject,       /* base class MetaObject accessor */
        thunk_igHotKeyBindingList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igHotKeyBindingList_className_0051df50,  /* class name */
        0x14,                                      /* instance size */
        igHotKeyBindingList_GetVTable,             /* vtable getter */
        0,                                         /* field adder */
        0,                                         /* extra callback item */
        g_igHotKeyBindingList_callbackList_004d0128  /* callback list */
    );
}
