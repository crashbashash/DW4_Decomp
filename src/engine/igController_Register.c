/* 0x00146910 igController_Register: registers class igController with the object system, derived from igEventProducer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igEventProducer_GetPublishedMetaObject[];
extern char igEventProducer_Register[];
extern char thunk_igController_GetMetaObject[];
extern char igController_className[];
extern char g_igController_metaObject[];
int WindowInputLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igController_InitFields();

void igController_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igController_metaObject,              /* published MetaObject slot */
        igEventProducer_Register,                        /* base class registrar */
        igEventProducer_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igController_GetMetaObject,                /* own MetaObject accessor (stored at +0x54) */
        igController_className,               /* class name */
        0x10,                                            /* instance size */
        0,                                               /* vtable getter */
        &igController_InitFields,                        /* field adder */
        0,                                               /* extra callback item */
        0                                                /* callback list */
    );
}
