/* 0x00451210 igEventReceiverOrderedList_Register: registers class igEventReceiverOrderedList with the object system, derived from igDependencyOrderedList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDependencyOrderedList_GetPublishedMetaObject_00233740[];
extern char igDependencyOrderedList_Register[];
extern char igEventReceiverOrderedList_GetVTable[];
extern char thunk_igEventReceiverOrderedList_GetMetaObject[];
extern char g_igEventReceiverOrderedList_callbackList_004d0720[];
extern char s_igEventReceiverOrderedList_className_0051e550[];
extern char g_igEventReceiverOrderedList_metaObject_0058c568[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();

void igEventReceiverOrderedList_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igEventReceiverOrderedList_metaObject_0058c568,        /* published MetaObject slot */
        igDependencyOrderedList_Register,                        /* base class registrar */
        igDependencyOrderedList_GetPublishedMetaObject_00233740, /* base class MetaObject accessor */
        thunk_igEventReceiverOrderedList_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        s_igEventReceiverOrderedList_className_0051e550,         /* class name */
        0x1C,                                                    /* instance size */
        igEventReceiverOrderedList_GetVTable,                    /* vtable getter */
        0,                                                       /* field adder */
        0,                                                       /* extra callback item */
        g_igEventReceiverOrderedList_callbackList_004d0720       /* callback list */
    );
}
