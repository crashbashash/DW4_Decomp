/* 0x002bdd40 igNonRefCountedObjectList_Register: registers class igNonRefCountedObjectList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igNonRefCountedObjectList_GetVTable[];
extern char thunk_igNonRefCountedObjectList_GetMetaObject[];
extern char igDataList_Register[];
extern char s_igNonRefCountedObjectList_className_004f6530[];
extern char g_igNonRefCountedObjectList_metaObject_00585bb0[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igNonRefCountedObjectList_InitFields_002bddc0[4];
void igNonRefCountedObjectList_Register(void) {
    /* Once-only static-init guard for this unit: the first call sets a gp-relative flag byte and
     * (in some units) chains the RunStaticInit thunks of related classes; per its asm, not a registrar. */
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNonRefCountedObjectList_metaObject_00585bb0,   /* published MetaObject slot */
        igDataList_Register,                               /* base class registrar */
        igDataList_GetPublishedMetaObject,                 /* base class MetaObject accessor */
        thunk_igNonRefCountedObjectList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igNonRefCountedObjectList_className_004f6530,    /* class name */
        0x14,                                              /* instance size */
        igNonRefCountedObjectList_GetVTable,               /* vtable getter */
        &igNonRefCountedObjectList_InitFields_002bddc0[0], /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
