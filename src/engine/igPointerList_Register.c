/* 0x002c9260 igPointerList_Register: registers class igPointerList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igPointerList_GetVTable[];
extern char thunk_igPointerList_GetMetaObject[];
extern char s_igPointerList_className_004f8518[];
extern char g_igPointerList_metaObject_005867e0[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igPointerList_InitFields_002c92e0[4];
void igPointerList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPointerList_metaObject_005867e0,   /* published MetaObject slot */
        igDataList_Register,                   /* base class registrar */
        igDataList_GetPublishedMetaObject,     /* base class MetaObject accessor */
        thunk_igPointerList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igPointerList_className_004f8518,    /* class name */
        0x14,                                  /* instance size */
        igPointerList_GetVTable,               /* vtable getter */
        &igPointerList_InitFields_002c92e0[0], /* field adder (post_init in data/reflection.json) */
        0,                                     /* extra callback-vector item (none; docs/engine/reflection-registration.md) */
        0                                      /* zero-terminated callback-vector item list (none) */
    );
}
