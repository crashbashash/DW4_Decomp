/* 0x001461a0 igEventProducerList_Register: registers class igEventProducerList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igEventProducerList_GetVTable[];
extern char thunk_igEventProducerList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igEventProducerList_callbackList_00487150[];
extern char s_igEventProducerList_className_004d6520[];
extern char g_igEventProducerList_metaObject_0055f5f8[];
int GpFlag_SetOnce_00145ce0();
int igMetaObject_RegisterClass();

void igEventProducerList_Register(void) {
    GpFlag_SetOnce_00145ce0();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igEventProducerList_metaObject_0055f5f8, /* published MetaObject slot */
        igObjectList_Register,                     /* base class registrar */
        igObjectList_GetPublishedMetaObject,       /* base class MetaObject accessor */
        thunk_igEventProducerList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igEventProducerList_className_004d6520,  /* class name */
        0x14,                                      /* instance size */
        igEventProducerList_GetVTable,             /* vtable getter */
        0,                                         /* field adder */
        0,                                         /* extra callback item */
        g_igEventProducerList_callbackList_00487150  /* callback list */
    );
}
