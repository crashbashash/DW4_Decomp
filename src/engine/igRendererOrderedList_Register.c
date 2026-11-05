/* 0x0044c690 igRendererOrderedList_Register: registers class igRendererOrderedList with the object system, derived from igDependencyOrderedList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDependencyOrderedList_GetPublishedMetaObject_00233740[];
extern char igDependencyOrderedList_Register[];
extern char igRendererOrderedList_GetVTable[];
extern char thunk_igRendererOrderedList_GetMetaObject[];
extern char g_igRendererOrderedList_callbackList_004cff88[];
extern char s_igRendererOrderedList_className_0051ddb0[];
extern char g_igRendererOrderedList_metaObject_0058c200[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();

void igRendererOrderedList_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRendererOrderedList_metaObject_0058c200,             /* published MetaObject slot */
        igDependencyOrderedList_Register,                        /* base class registrar */
        igDependencyOrderedList_GetPublishedMetaObject_00233740, /* base class MetaObject accessor */
        thunk_igRendererOrderedList_GetMetaObject,               /* own MetaObject accessor (stored at +0x54) */
        s_igRendererOrderedList_className_0051ddb0,              /* class name */
        0x1C,                                                    /* instance size */
        igRendererOrderedList_GetVTable,                         /* vtable getter */
        0,                                                       /* field adder */
        0,                                                       /* extra callback item */
        g_igRendererOrderedList_callbackList_004cff88            /* callback list */
    );
}
