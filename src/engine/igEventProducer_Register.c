/* 0x00146280 igEventProducer_Register: registers class igEventProducer with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igEventProducer_GetMetaObject[];
extern char igObject_Register[];
extern char igEventProducer_className[];
extern char g_igEventProducer_metaObject[];
int GpFlag_SetOnce_00145ce0();
int igMetaObject_RegisterClass();

void igEventProducer_Register(void) {
    GpFlag_SetOnce_00145ce0();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igEventProducer_metaObject, /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igEventProducer_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igEventProducer_className,  /* class name */
        8,                                     /* instance size */
        0,                                     /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
