/* 0x00227300 igListenerBase_Register: registers class igListenerBase with the object system, derived from igBase.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igBase_GetPublishedMetaObject[];
extern char igListenerBase_GetVTable[];
extern char thunk_igListenerBase_GetMetaObject[];
extern char igBase_Register[];
extern char igListenerBase_className[];
extern char g_igListenerBase_metaObject[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();

void igListenerBase_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igListenerBase_metaObject,   /* published MetaObject slot */
        igBase_Register,                        /* base class registrar */
        igBase_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igListenerBase_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igListenerBase_className,    /* class name */
        0x20,                                   /* instance size */
        igListenerBase_GetVTable,               /* vtable getter */
        0,                                      /* field adder */
        0,                                      /* extra callback item */
        0                                       /* callback list */
    );
}
