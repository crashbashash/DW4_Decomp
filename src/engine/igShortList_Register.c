/* 0x002c9eb0 igShortList_Register: static-init registration of igShortList (an igDataList of signed 16-bit elements)
 * with the object system.  The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1 (finding #358); names from data/reflection.json.
 * FUN_002b5d50 is the set-once latch every registrar of this group calls first
 * (a gp byte flag guards a few shared one-time registrations). */
extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igShortList_GetVTable[];
extern char thunk_igShortList_GetMetaObject[];
extern char s_igShortList_className_004f8590[];
extern char g_igShortList_metaObject_00586830[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igShortList_InitFields_002c9f30[4];
void igShortList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igShortList_metaObject_00586830,   /* published MetaObject slot */
        igDataList_Register,                 /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igShortList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igShortList_className_004f8590,    /* class name */
        0x14,                                /* instance size */
        igShortList_GetVTable,               /* vtable getter */
        &igShortList_InitFields_002c9f30[0], /* field adder (class InitFields) */
        0,                                   /* extra callback item */
        0                                    /* callback list */
    );
}
