/* Static-init registration of igVec4ucList (an igDataList of 4-component unsigned-char vector
 * elements). FUN_00186a40 is the set-once latch every registrar of this group calls first (a gp
 * byte flag guards a few shared one-time registrations). */
extern char igDataList_GetPublishedMetaObject[];
extern char igVec4ucList_GetVTable[];
extern char thunk_igVec4ucList_GetMetaObject[];
extern char igDataList_Register[];
extern char igVec4ucList_className[];
extern char g_igVec4ucList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
extern int igVec4ucList_InitFields_00189fa0[4];
void igVec4ucList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVec4ucList_metaObject,
        igDataList_Register,                  /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        thunk_igVec4ucList_GetMetaObject,
        igVec4ucList_className,
        0x14, /* instance size */
        igVec4ucList_GetVTable,
        &igVec4ucList_InitFields_00189fa0[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}
