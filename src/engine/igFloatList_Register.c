/* 0x002c9870 igFloatList_Register: registers class igFloatList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igFloatList_GetVTable[];
extern char thunk_igFloatList_GetMetaObject[];
extern char s_igFloatList_className_004f8550[];
extern char g_igFloatList_metaObject_00586808[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igFloatList_InitFields_002c98f0[4];
void igFloatList_Register(void) {
    /* Once-only static-init guard for this unit: the first call sets a gp-relative flag byte and
     * (in some units) chains the RunStaticInit thunks of related classes; per its asm, not a registrar. */
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFloatList_metaObject_00586808,   /* published MetaObject slot */
        igDataList_Register,                 /* base class registrar */
        igDataList_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igFloatList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igFloatList_className_004f8550,    /* class name */
        0x14,                                /* instance size */
        igFloatList_GetVTable,               /* vtable getter */
        &igFloatList_InitFields_002c98f0[0], /* field adder */
        0,                                   /* extra callback item */
        0                                    /* callback list */
    );
}
