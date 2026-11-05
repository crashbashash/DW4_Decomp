/* 0x0044ca90 igOnOffValueObserver_Register: registers class igOnOffValueObserver with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igOnOffValueObserver_GetVTable[];
extern char thunk_igOnOffValueObserver_GetMetaObject[];
extern char igView_GetPublishedMetaObject_0044cb20[];
extern char g_igOnOffValueObserver_callbackList_004cffc0[];
extern char s_igOnOffValueObserver_className_0051de10[];
extern char g_igOnOffValueObserver_metaObject_0058c220[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igOnOffValueObserver_InitFields();

void igOnOffValueObserver_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igOnOffValueObserver_metaObject_0058c220, /* published MetaObject slot */
        igView_Register,                            /* base class registrar */
        igView_GetPublishedMetaObject_0044cb20,     /* base class MetaObject accessor */
        thunk_igOnOffValueObserver_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igOnOffValueObserver_className_0051de10,  /* class name */
        0x10,                                       /* instance size */
        igOnOffValueObserver_GetVTable,             /* vtable getter */
        &igOnOffValueObserver_InitFields,           /* field adder */
        0,                                          /* extra callback item */
        g_igOnOffValueObserver_callbackList_004cffc0  /* callback list */
    );
}
