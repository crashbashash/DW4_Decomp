/* 0x00146710 igControllerManager_Register: registers class igControllerManager with the object system, derived from igEventProducer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igEventProducer_GetPublishedMetaObject_00145e70[];
extern char igEventProducer_Register[];
extern char thunk_igControllerManager_GetMetaObject[];
extern char g_igControllerManager_callbackList_00487260[];
extern char s_igControllerManager_className_004d67b0[];
extern char g_igControllerManager_metaObject_0055f698[];
int GpFlag_SetOnce_00145ce0();
int igMetaObject_RegisterClass();
int igControllerManager_InitFields();

void igControllerManager_Register(void) {
    GpFlag_SetOnce_00145ce0();
    igMetaObject_RegisterClass(
        1,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igControllerManager_metaObject_0055f698,       /* published MetaObject slot */
        igEventProducer_Register,                        /* base class registrar */
        igEventProducer_GetPublishedMetaObject_00145e70, /* base class MetaObject accessor */
        thunk_igControllerManager_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igControllerManager_className_004d67b0,        /* class name */
        0xC,                                             /* instance size */
        0,                                               /* vtable getter */
        &igControllerManager_InitFields,                 /* field adder */
        0,                                               /* extra callback item */
        g_igControllerManager_callbackList_00487260      /* callback list */
    );
}
