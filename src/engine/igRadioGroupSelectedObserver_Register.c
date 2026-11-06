/* 0x0044ccc0 igRadioGroupSelectedObserver_Register: registers class igRadioGroupSelectedObserver with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char igRadioGroupSelectedObserver_GetVTable[];
extern char thunk_igRadioGroupSelectedObserver_GetMetaObject[];
extern char g_igRadioGroupSelectedObserver_callbackList[];
extern char igRadioGroupSelectedObserver_className[];
extern char g_igRadioGroupSelectedObserver_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igRadioGroupSelectedObserver_InitFields();

void igRadioGroupSelectedObserver_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                                  /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRadioGroupSelectedObserver_metaObject, /* published MetaObject slot */
        igView_Register,                                    /* base class registrar */
        igView_GetPublishedMetaObject,             /* base class MetaObject accessor */
        thunk_igRadioGroupSelectedObserver_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igRadioGroupSelectedObserver_className,  /* class name */
        0x10,                                               /* instance size */
        igRadioGroupSelectedObserver_GetVTable,             /* vtable getter */
        &igRadioGroupSelectedObserver_InitFields,           /* field adder */
        0,                                                  /* extra callback item */
        g_igRadioGroupSelectedObserver_callbackList  /* callback list */
    );
}
