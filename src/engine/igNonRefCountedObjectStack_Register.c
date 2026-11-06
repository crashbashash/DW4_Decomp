/* 0x001e4440 igNonRefCountedObjectStack_Register: registers class igNonRefCountedObjectStack with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igNonRefCountedObjectStack_GetVTable[];
extern char thunk_igNonRefCountedObjectStack_GetMetaObject[];
extern char igDataList_Register[];
extern char igNonRefCountedObjectStack_className[];
extern char g_igNonRefCountedObjectStack_metaObject[];
int GpFlag_SetOnce_001e3ff0();
int igMetaObject_RegisterClass();
extern int igNonRefCountedObjectStack_InitFields_001e44c0[4];
void igNonRefCountedObjectStack_Register(void) {
    GpFlag_SetOnce_001e3ff0();
    igMetaObject_RegisterClass(
        0,                                                  /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNonRefCountedObjectStack_metaObject,   /* published MetaObject slot */
        igDataList_Register,                                /* base class registrar */
        igDataList_GetPublishedMetaObject,                  /* base class MetaObject accessor */
        thunk_igNonRefCountedObjectStack_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igNonRefCountedObjectStack_className,    /* class name */
        0x14,                                               /* instance size */
        igNonRefCountedObjectStack_GetVTable,               /* vtable getter */
        &igNonRefCountedObjectStack_InitFields_001e44c0[0], /* field adder (post_init in data/reflection.json) */
        0,                                                  /* extra callback-vector item (none) */
        0                                                   /* zero-terminated callback-vector item list (none) */
    );
}
