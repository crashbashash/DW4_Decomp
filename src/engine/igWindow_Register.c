/* 0x00145df0 igWindow_Register: registers class igWindow with the object system, derived from igEventProducer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char thunk_igWindow_GetMetaObject[];
extern char igEventProducer_GetPublishedMetaObject[];
extern char igEventProducer_Register[];
extern char igWindow_className[];
extern char g_igWindow_metaObject[];
int GpFlag_SetOnce_00145ce0();
int igMetaObject_RegisterClass();
void FUN_00145e80(void);  /* code at 0x145e80, passed by address (was DAT_145e80; docs/engine/function-inventory.md) */
void igWindow_Register(void) {
    GpFlag_SetOnce_00145ce0();
    igMetaObject_RegisterClass(
        1,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igWindow_metaObject,                  /* published MetaObject slot */
        igEventProducer_Register,                        /* base class registrar */
        igEventProducer_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igWindow_GetMetaObject,                    /* own MetaObject accessor (stored at +0x54) */
        igWindow_className,                   /* class name */
        8,                                               /* instance size */
        0,                                               /* vtable getter */
        FUN_00145e80,                                /* field adder */
        0,                                               /* extra callback item */
        0                                                /* callback list */
    );
}
