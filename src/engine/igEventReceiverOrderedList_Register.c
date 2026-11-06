/* 0x00451210 igEventReceiverOrderedList_Register: registers class igEventReceiverOrderedList with the object system, derived from igDependencyOrderedList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDependencyOrderedList_GetPublishedMetaObject[];
extern char igDependencyOrderedList_Register[];
extern char igEventReceiverOrderedList_GetVTable[];
extern char thunk_igEventReceiverOrderedList_GetMetaObject[];
extern char g_igEventReceiverOrderedList_callbackList[];
extern char igEventReceiverOrderedList_className[];
extern char g_igEventReceiverOrderedList_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();

void igEventReceiverOrderedList_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igEventReceiverOrderedList_metaObject,        /* published MetaObject slot */
        igDependencyOrderedList_Register,                        /* base class registrar */
        igDependencyOrderedList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igEventReceiverOrderedList_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igEventReceiverOrderedList_className,         /* class name */
        0x1C,                                                    /* instance size */
        igEventReceiverOrderedList_GetVTable,                    /* vtable getter */
        0,                                                       /* field adder */
        0,                                                       /* extra callback item */
        g_igEventReceiverOrderedList_callbackList       /* callback list */
    );
}
