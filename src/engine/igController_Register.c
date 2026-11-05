/* 0x00146910 igController_Register: registers class igController with the object system, derived from igEventProducer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igEventProducer_GetPublishedMetaObject_00145e70[];
extern char igEventProducer_Register[];
extern char thunk_igController_GetMetaObject[];
extern char s_igController_className_004d6bd0[];
extern char g_igController_metaObject_0055f6b0[];
int GpFlag_SetOnce_00145ce0();
int igMetaObject_RegisterClass();
int igController_InitFields();

void igController_Register(void) {
    GpFlag_SetOnce_00145ce0();
    igMetaObject_RegisterClass(
        1,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igController_metaObject_0055f6b0,              /* published MetaObject slot */
        igEventProducer_Register,                        /* base class registrar */
        igEventProducer_GetPublishedMetaObject_00145e70, /* base class MetaObject accessor */
        thunk_igController_GetMetaObject,                /* own MetaObject accessor (stored at +0x54) */
        s_igController_className_004d6bd0,               /* class name */
        0x10,                                            /* instance size */
        0,                                               /* vtable getter */
        &igController_InitFields,                        /* field adder */
        0,                                               /* extra callback item */
        0                                                /* callback list */
    );
}
