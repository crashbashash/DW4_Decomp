/* 0x001528f0 igPsx2LongList_Register: registers class igPsx2LongList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igPsx2LongList_GetVTable[];
extern char thunk_igPsx2LongList_GetMetaObject[];
extern char igDataList_Register[];
extern char igPsx2LongList_className[];
extern char g_igPsx2LongList_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int igPsx2LongList_InitFields_00152970[4];
void igPsx2LongList_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2LongList_metaObject,   /* published MetaObject slot */
        igDataList_Register,                    /* base class registrar */
        igDataList_GetPublishedMetaObject,      /* base class MetaObject accessor */
        thunk_igPsx2LongList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igPsx2LongList_className,    /* class name */
        0x14,                                   /* instance size */
        igPsx2LongList_GetVTable,               /* vtable getter */
        &igPsx2LongList_InitFields_00152970[0], /* field adder (post_init in data/reflection.json) */
        0,                                      /* extra callback-vector item (none; docs/engine/reflection-registration.md) */
        0                                       /* zero-terminated callback-vector item list (none) */
    );
}
