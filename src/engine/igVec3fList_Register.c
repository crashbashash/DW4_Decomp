/* 0x0018a190 igVec3fList_Register: static-init registration of igVec3fList (an igDataList of 3-component float vector elements)
 * with the object system.  The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1 (finding #358); names from data/reflection.json.
 * FUN_00186a40 is the set-once latch every registrar of this group calls first
 * (a gp byte flag guards a few shared one-time registrations). */
extern char igDataList_GetPublishedMetaObject[];
extern char igVec3fList_GetVTable[];
extern char thunk_igVec3fList_GetMetaObject[];
extern char igDataList_Register[];
extern char igVec3fList_className[];
extern char g_igVec3fList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
extern int igVec3fList_InitFields_0018a210[4];
void igVec3fList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVec3fList_metaObject,   /* published MetaObject slot */
        igDataList_Register,                 /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igVec3fList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igVec3fList_className,    /* class name */
        0x14,                                /* instance size */
        igVec3fList_GetVTable,               /* vtable getter */
        &igVec3fList_InitFields_0018a210[0], /* field adder (class InitFields) */
        0,                                   /* extra callback item */
        0                                    /* callback list */
    );
}
