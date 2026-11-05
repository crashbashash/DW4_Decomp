/* 0x00189f20 igVec4ucList_Register: static-init registration of igVec4ucList (an igDataList of 4-component unsigned-char vector elements)
 * with the object system.  The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1 (finding #358); names from data/reflection.json.
 * FUN_00186a40 is the set-once latch every registrar of this group calls first
 * (a gp byte flag guards a few shared one-time registrations). */
extern char igDataList_GetPublishedMetaObject[];
extern char igVec4ucList_GetVTable[];
extern char thunk_igVec4ucList_GetMetaObject[];
extern char igDataList_Register[];
extern char s_igVec4ucList_className_004e0cc8[];
extern char g_igVec4ucList_metaObject_00561098[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
extern int igVec4ucList_InitFields_00189fa0[4];
void igVec4ucList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                    /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVec4ucList_metaObject_00561098,   /* published MetaObject slot */
        igDataList_Register,                  /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,    /* base class MetaObject accessor */
        thunk_igVec4ucList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igVec4ucList_className_004e0cc8,    /* class name */
        0x14,                                 /* instance size */
        igVec4ucList_GetVTable,               /* vtable getter */
        &igVec4ucList_InitFields_00189fa0[0], /* field adder (class InitFields) */
        0,                                    /* extra callback item */
        0                                     /* callback list */
    );
}
