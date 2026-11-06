/* 0x0044ef10 igMousePosObserver_Register: registers class igMousePosObserver with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char igMousePosObserver_GetVTable[];
extern char thunk_igMousePosObserver_GetMetaObject[];
extern char g_igMousePosObserver_callbackList[];
extern char igMousePosObserver_className[];
extern char g_igMousePosObserver_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igMousePosObserver_InitFields();

void igMousePosObserver_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMousePosObserver_metaObject, /* published MetaObject slot */
        igView_Register,                          /* base class registrar */
        igView_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igMousePosObserver_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igMousePosObserver_className,  /* class name */
        0x64,                                     /* instance size */
        igMousePosObserver_GetVTable,             /* vtable getter */
        &igMousePosObserver_InitFields,           /* field adder */
        0,                                        /* extra callback item */
        g_igMousePosObserver_callbackList  /* callback list */
    );
}
