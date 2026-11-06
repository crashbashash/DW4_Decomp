/* 0x00189a90 igMatrix44fList_Register: registers class igMatrix44fList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igMatrix44fList_GetVTable[];
extern char thunk_igMatrix44fList_GetMetaObject[];
extern char igDataList_Register[];
extern char igMatrix44fList_className[];
extern char g_igMatrix44fList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
extern int igMatrix44fList_InitFields_00189b10[4];
void igMatrix44fList_Register(void) {
    /* Once-only static-init guard for this unit: the first call sets a gp-relative flag byte and
     * (in some units) chains the RunStaticInit thunks of related classes; per its asm, not a registrar. */
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMatrix44fList_metaObject,   /* published MetaObject slot */
        igDataList_Register,                     /* base class registrar */
        igDataList_GetPublishedMetaObject,       /* base class MetaObject accessor */
        thunk_igMatrix44fList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igMatrix44fList_className,    /* class name */
        0x14,                                    /* instance size */
        igMatrix44fList_GetVTable,               /* vtable getter */
        &igMatrix44fList_InitFields_00189b10[0], /* field adder */
        0,                                       /* extra callback item */
        0                                        /* callback list */
    );
}
