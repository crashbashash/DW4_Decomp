/* 0x0044f190 igWindowSizeObserver_Register: registers class igWindowSizeObserver with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igView_GetPublishedMetaObject_0044cb20[];
extern char igWindowSizeObserver_GetVTable[];
extern char thunk_igWindowSizeObserver_GetMetaObject[];
extern char s_igWindowSizeObserver_className_0051e1d0[];
extern char g_igWindowSizeObserver_metaObject_0058c3c0[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();

void igWindowSizeObserver_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igWindowSizeObserver_metaObject_0058c3c0, /* published MetaObject slot */
        igView_Register,                            /* base class registrar */
        igView_GetPublishedMetaObject_0044cb20,     /* base class MetaObject accessor */
        thunk_igWindowSizeObserver_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igWindowSizeObserver_className_0051e1d0,  /* class name */
        0xC,                                        /* instance size */
        igWindowSizeObserver_GetVTable,             /* vtable getter */
        0,                                          /* field adder */
        0,                                          /* extra callback item */
        0                                           /* callback list */
    );
}
