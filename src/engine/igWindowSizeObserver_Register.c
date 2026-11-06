/* 0x0044f190 igWindowSizeObserver_Register: registers class igWindowSizeObserver with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char igWindowSizeObserver_GetVTable[];
extern char thunk_igWindowSizeObserver_GetMetaObject[];
extern char igWindowSizeObserver_className[];
extern char g_igWindowSizeObserver_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igWindowSizeObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igWindowSizeObserver_metaObject, /* published MetaObject slot */
        igView_Register,                            /* base class registrar */
        igView_GetPublishedMetaObject,     /* base class MetaObject accessor */
        thunk_igWindowSizeObserver_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igWindowSizeObserver_className,  /* class name */
        0xC,                                        /* instance size */
        igWindowSizeObserver_GetVTable,             /* vtable getter */
        0,                                          /* field adder */
        0,                                          /* extra callback item */
        0                                           /* callback list */
    );
}
