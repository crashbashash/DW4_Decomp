/* 0x002b9210 igStringRefList_Register: static-init registration of igStringRefList (an igDataList of string-reference elements)
 * with the object system.  The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1 (finding #358); names from data/reflection.json.
 * FUN_002b5d50 is the set-once latch every registrar of this group calls first
 * (a gp byte flag guards a few shared one-time registrations). */
extern char igDataList_GetPublishedMetaObject[];
extern char igStringRefList_GetVTable[];
extern char thunk_igStringRefList_GetMetaObject[];
extern char igDataList_Register[];
extern char igStringRefList_className[];
extern char g_igStringRefList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igStringRefList_InitFields_002b9290[4];
void igStringRefList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStringRefList_metaObject,   /* published MetaObject slot */
        igDataList_Register,                     /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,       /* base class MetaObject accessor */
        thunk_igStringRefList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igStringRefList_className,    /* class name */
        0x14,                                    /* instance size */
        igStringRefList_GetVTable,               /* vtable getter */
        &igStringRefList_InitFields_002b9290[0], /* field adder (class InitFields) */
        0,                                       /* extra callback item */
        0                                        /* callback list */
    );
}
