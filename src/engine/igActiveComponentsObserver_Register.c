/* 0x0044eb60 igActiveComponentsObserver_Register: registers class igActiveComponentsObserver with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igView_GetPublishedMetaObject_0044cb20[];
extern char igActiveComponentsObserver_GetVTable[];
extern char thunk_igActiveComponentsObserver_GetMetaObject[];
extern char g_igActiveComponentsObserver_callbackList_004d02c0[];
extern char s_igActiveComponentsObserver_className_0051e0b0[];
extern char g_igActiveComponentsObserver_metaObject_0058c360[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igActiveComponentsObserver_InitFields();

void igActiveComponentsObserver_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                                /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igActiveComponentsObserver_metaObject_0058c360, /* published MetaObject slot */
        igView_Register,                                  /* base class registrar */
        igView_GetPublishedMetaObject_0044cb20,           /* base class MetaObject accessor */
        thunk_igActiveComponentsObserver_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igActiveComponentsObserver_className_0051e0b0,  /* class name */
        0x18,                                             /* instance size */
        igActiveComponentsObserver_GetVTable,             /* vtable getter */
        &igActiveComponentsObserver_InitFields,           /* field adder */
        0,                                                /* extra callback item */
        g_igActiveComponentsObserver_callbackList_004d02c0  /* callback list */
    );
}
