/* 0x002ca770 igLongList_Register: registers class igLongList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igLongList_GetVTable[];
extern char thunk_igLongList_GetMetaObject[];
extern char igLongList_className[];
extern char g_igLongList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igLongList_InitFields_002ca7f0[4];
void igLongList_Register(void) {
    /* Once-only static-init guard for this unit: the first call sets a gp-relative flag byte and
     * (in some units) chains the RunStaticInit thunks of related classes; per its asm, not a registrar. */
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                  /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLongList_metaObject,   /* published MetaObject slot */
        igDataList_Register,                /* base class registrar */
        igDataList_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igLongList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igLongList_className,    /* class name */
        0x14,                               /* instance size */
        igLongList_GetVTable,               /* vtable getter */
        &igLongList_InitFields_002ca7f0[0], /* field adder */
        0,                                  /* extra callback item */
        0                                   /* callback list */
    );
}
