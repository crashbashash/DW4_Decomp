/* 0x002ca540 igUnsignedIntList_Register: static-init registration of igUnsignedIntList (an igDataList of unsigned 32-bit elements)
 * with the object system.  The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1 (finding #358); names from data/reflection.json.
 * FUN_002b5d50 is the set-once latch every registrar of this group calls first
 * (a gp byte flag guards a few shared one-time registrations). */
extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igUnsignedIntList_GetVTable[];
extern char thunk_igUnsignedIntList_GetMetaObject[];
extern char s_igUnsignedIntList_className_004f85e0[];
extern char g_igUnsignedIntList_metaObject_00586858[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igUnsignedIntList_InitFields_002ca5c0[4];
void igUnsignedIntList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igUnsignedIntList_metaObject_00586858,   /* published MetaObject slot */
        igDataList_Register,                       /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,         /* base class MetaObject accessor */
        thunk_igUnsignedIntList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igUnsignedIntList_className_004f85e0,    /* class name */
        0x14,                                      /* instance size */
        igUnsignedIntList_GetVTable,               /* vtable getter */
        &igUnsignedIntList_InitFields_002ca5c0[0], /* field adder (class InitFields) */
        0,                                         /* extra callback item */
        0                                          /* callback list */
    );
}
