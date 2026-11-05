/* 0x00227630 igIterateGraph_Register: registers class igIterateGraph with the object system, derived from igIterator.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igIterator_Register[];
extern char igIterator_GetPublishedMetaObject_00227450[];
extern char igIterateGraph_GetVTable[];
extern char thunk_igIterateGraph_GetMetaObject[];
extern char g_igIterateGraph_callbackList_00497d30[];
extern char s_igIterateGraph_className_004e7c30[];
extern char g_igIterateGraph_metaObject_0056d948[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();
int igIterateGraph_InitFields();

void igIterateGraph_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIterateGraph_metaObject_0056d948,       /* published MetaObject slot */
        igIterator_Register,                        /* base class registrar */
        igIterator_GetPublishedMetaObject_00227450, /* base class MetaObject accessor */
        thunk_igIterateGraph_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igIterateGraph_className_004e7c30,        /* class name */
        0x14,                                       /* instance size */
        igIterateGraph_GetVTable,                   /* vtable getter */
        &igIterateGraph_InitFields,                 /* field adder */
        0,                                          /* extra callback item */
        g_igIterateGraph_callbackList_00497d30      /* callback list */
    );
}
