/* 0x00189d00 igQuaternionfList_Register: registers class igQuaternionfList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igQuaternionfList_GetVTable[];
extern char thunk_igQuaternionfList_GetMetaObject[];
extern char igDataList_Register[];
extern char igQuaternionfList_className[];
extern char g_igQuaternionfList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
extern int igQuaternionfList_InitFields_00189d80[4];
void igQuaternionfList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igQuaternionfList_metaObject,   /* published MetaObject slot */
        igDataList_Register,                       /* base class registrar */
        igDataList_GetPublishedMetaObject,         /* base class MetaObject accessor */
        thunk_igQuaternionfList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igQuaternionfList_className,    /* class name */
        0x14,                                      /* instance size */
        igQuaternionfList_GetVTable,               /* vtable getter */
        &igQuaternionfList_InitFields_00189d80[0], /* field adder (post_init in data/reflection.json) */
        0,                                         /* extra callback-vector item (none) */
        0                                          /* zero-terminated callback-vector item list (none) */
    );
}
