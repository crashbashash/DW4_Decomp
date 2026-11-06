/* 0x00227630 igIterateGraph_Register: registers class igIterateGraph with the object system, derived from igIterator.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igIterator_Register[];
extern char igIterator_GetPublishedMetaObject[];
extern char igIterateGraph_GetVTable[];
extern char thunk_igIterateGraph_GetMetaObject[];
extern char g_igIterateGraph_callbackList[];
extern char igIterateGraph_className[];
extern char g_igIterateGraph_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igIterateGraph_InitFields();

void igIterateGraph_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIterateGraph_metaObject,       /* published MetaObject slot */
        igIterator_Register,                        /* base class registrar */
        igIterator_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igIterateGraph_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igIterateGraph_className,        /* class name */
        0x14,                                       /* instance size */
        igIterateGraph_GetVTable,                   /* vtable getter */
        &igIterateGraph_InitFields,                 /* field adder */
        0,                                          /* extra callback item */
        g_igIterateGraph_callbackList      /* callback list */
    );
}
