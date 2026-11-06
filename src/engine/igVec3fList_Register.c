/* Static-init registration of igVec3fList (an igDataList of 3-component float vector elements).
 * FUN_00186a40 is the set-once latch every registrar of this group calls first (a gp byte flag
 * guards a few shared one-time registrations). */
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
        0, /* abstract */
        g_igVec3fList_metaObject,
        igDataList_Register,                 /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        thunk_igVec3fList_GetMetaObject,
        igVec3fList_className,
        0x14, /* instance size */
        igVec3fList_GetVTable,
        &igVec3fList_InitFields_0018a210[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}
