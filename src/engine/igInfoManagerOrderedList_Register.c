/* 0x002336c0 igInfoManagerOrderedList_Register: registers class igInfoManagerOrderedList with the object system, derived from igDependencyOrderedList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInfoManagerOrderedList_GetVTable[];
extern char thunk_igInfoManagerOrderedList_GetMetaObject[];
extern char igDependencyOrderedList_GetPublishedMetaObject_00233740[];
extern char igDependencyOrderedList_Register[];
extern char g_igInfoManagerOrderedList_callbackList_00498238[];
extern char s_igInfoManagerOrderedList_className_004e8750[];
extern char g_igInfoManagerOrderedList_metaObject_0056dc28[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();

void igInfoManagerOrderedList_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        0,                                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igInfoManagerOrderedList_metaObject_0056dc28,          /* published MetaObject slot */
        igDependencyOrderedList_Register,                        /* base class registrar */
        igDependencyOrderedList_GetPublishedMetaObject_00233740, /* base class MetaObject accessor */
        thunk_igInfoManagerOrderedList_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        s_igInfoManagerOrderedList_className_004e8750,           /* class name */
        0x1C,                                                    /* instance size */
        igInfoManagerOrderedList_GetVTable,                      /* vtable getter */
        0,                                                       /* field adder */
        0,                                                       /* extra callback item */
        g_igInfoManagerOrderedList_callbackList_00498238         /* callback list */
    );
}
