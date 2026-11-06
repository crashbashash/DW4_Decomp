/* 0x00231880 igMessageReceiverList_Register: registers class igMessageReceiverList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igMessageReceiverList_GetVTable[];
extern char thunk_igMessageReceiverList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igMessageReceiverList_callbackList[];
extern char igMessageReceiverList_className[];
extern char g_igMessageReceiverList_metaObject[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();

void igMessageReceiverList_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMessageReceiverList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                       /* base class registrar */
        igObjectList_GetPublishedMetaObject,         /* base class MetaObject accessor */
        thunk_igMessageReceiverList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igMessageReceiverList_className,  /* class name */
        0x14,                                        /* instance size */
        igMessageReceiverList_GetVTable,             /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igMessageReceiverList_callbackList  /* callback list */
    );
}
