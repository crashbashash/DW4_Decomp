/* 0x002336c0 igInfoManagerOrderedList_Register: registers class igInfoManagerOrderedList with the object system, derived from igDependencyOrderedList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInfoManagerOrderedList_GetVTable[];
extern char thunk_igInfoManagerOrderedList_GetMetaObject[];
extern char igDependencyOrderedList_GetPublishedMetaObject[];
extern char igDependencyOrderedList_Register[];
extern char g_igInfoManagerOrderedList_callbackList[];
extern char igInfoManagerOrderedList_className[];
extern char g_igInfoManagerOrderedList_metaObject[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();

void igInfoManagerOrderedList_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        0,                                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igInfoManagerOrderedList_metaObject,          /* published MetaObject slot */
        igDependencyOrderedList_Register,                        /* base class registrar */
        igDependencyOrderedList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igInfoManagerOrderedList_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        igInfoManagerOrderedList_className,           /* class name */
        0x1C,                                                    /* instance size */
        igInfoManagerOrderedList_GetVTable,                      /* vtable getter */
        0,                                                       /* field adder */
        0,                                                       /* extra callback item */
        g_igInfoManagerOrderedList_callbackList         /* callback list */
    );
}
