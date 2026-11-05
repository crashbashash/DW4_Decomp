/* 0x002c9a90 igUnsignedCharList_Register: static-init registration of igUnsignedCharList (an igDataList of unsigned 8-bit elements)
 * with the object system.  The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1 (finding #358); names from data/reflection.json.
 * FUN_002b5d50 is the set-once latch every registrar of this group calls first
 * (a gp byte flag guards a few shared one-time registrations). */
extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igUnsignedCharList_GetVTable[];
extern char thunk_igUnsignedCharList_GetMetaObject[];
extern char s_igUnsignedCharList_className_004f8560[];
extern char g_igUnsignedCharList_metaObject_00586818[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igUnsignedCharList_InitFields_002c9b10[4];
void igUnsignedCharList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igUnsignedCharList_metaObject_00586818,   /* published MetaObject slot */
        igDataList_Register,                        /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,          /* base class MetaObject accessor */
        thunk_igUnsignedCharList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igUnsignedCharList_className_004f8560,    /* class name */
        0x14,                                       /* instance size */
        igUnsignedCharList_GetVTable,               /* vtable getter */
        &igUnsignedCharList_InitFields_002c9b10[0], /* field adder (class InitFields) */
        0,                                          /* extra callback item */
        0                                           /* callback list */
    );
}
