/* 0x00146710 igControllerManager_Register: registers class igControllerManager with the object system, derived from igEventProducer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igEventProducer_GetPublishedMetaObject[];
extern char igEventProducer_Register[];
extern char thunk_igControllerManager_GetMetaObject[];
extern char g_igControllerManager_callbackList[];
extern char igControllerManager_className[];
extern char g_igControllerManager_metaObject[];
int GpFlag_SetOnce_00145ce0();
int igMetaObject_RegisterClass();
int igControllerManager_InitFields();

void igControllerManager_Register(void) {
    GpFlag_SetOnce_00145ce0();
    igMetaObject_RegisterClass(
        1,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igControllerManager_metaObject,       /* published MetaObject slot */
        igEventProducer_Register,                        /* base class registrar */
        igEventProducer_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igControllerManager_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igControllerManager_className,        /* class name */
        0xC,                                             /* instance size */
        0,                                               /* vtable getter */
        &igControllerManager_InitFields,                 /* field adder */
        0,                                               /* extra callback item */
        g_igControllerManager_callbackList      /* callback list */
    );
}
