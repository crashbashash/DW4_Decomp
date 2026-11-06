/* 0x0044ca90 igOnOffValueObserver_Register: registers class igOnOffValueObserver with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igOnOffValueObserver_GetVTable[];
extern char thunk_igOnOffValueObserver_GetMetaObject[];
extern char igView_GetPublishedMetaObject[];
extern char g_igOnOffValueObserver_callbackList[];
extern char igOnOffValueObserver_className[];
extern char g_igOnOffValueObserver_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igOnOffValueObserver_InitFields();

void igOnOffValueObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igOnOffValueObserver_metaObject, /* published MetaObject slot */
        igView_Register,                            /* base class registrar */
        igView_GetPublishedMetaObject,     /* base class MetaObject accessor */
        thunk_igOnOffValueObserver_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igOnOffValueObserver_className,  /* class name */
        0x10,                                       /* instance size */
        igOnOffValueObserver_GetVTable,             /* vtable getter */
        &igOnOffValueObserver_InitFields,           /* field adder */
        0,                                          /* extra callback item */
        g_igOnOffValueObserver_callbackList  /* callback list */
    );
}
