/* 0x0044ccc0 igRadioGroupSelectedObserver_Register: registers class igRadioGroupSelectedObserver with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igView_GetPublishedMetaObject_0044cb20[];
extern char igRadioGroupSelectedObserver_GetVTable[];
extern char thunk_igRadioGroupSelectedObserver_GetMetaObject[];
extern char g_igRadioGroupSelectedObserver_callbackList_004cffe8[];
extern char s_igRadioGroupSelectedObserver_className_0051de30[];
extern char g_igRadioGroupSelectedObserver_metaObject_0058c230[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igRadioGroupSelectedObserver_InitFields();

void igRadioGroupSelectedObserver_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                                  /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRadioGroupSelectedObserver_metaObject_0058c230, /* published MetaObject slot */
        igView_Register,                                    /* base class registrar */
        igView_GetPublishedMetaObject_0044cb20,             /* base class MetaObject accessor */
        thunk_igRadioGroupSelectedObserver_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igRadioGroupSelectedObserver_className_0051de30,  /* class name */
        0x10,                                               /* instance size */
        igRadioGroupSelectedObserver_GetVTable,             /* vtable getter */
        &igRadioGroupSelectedObserver_InitFields,           /* field adder */
        0,                                                  /* extra callback item */
        g_igRadioGroupSelectedObserver_callbackList_004cffe8  /* callback list */
    );
}
