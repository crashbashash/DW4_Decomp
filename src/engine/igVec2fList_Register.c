/* Static-init registration of igVec2fList (an igDataList of 2-component float vector elements).
 * FUN_00186a40 is the set-once latch every registrar of this group calls first (a gp byte flag
 * guards a few shared one-time registrations). */
extern char igDataList_GetPublishedMetaObject[];
extern char igVec2fList_GetVTable[];
extern char thunk_igVec2fList_GetMetaObject[];
extern char igDataList_Register[];
extern char igVec2fList_className[];
extern char g_igVec2fList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
extern int igVec2fList_InitFields_0018a430[4];
void igVec2fList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVec2fList_metaObject,
        igDataList_Register,                 /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        thunk_igVec2fList_GetMetaObject,
        igVec2fList_className,
        0x14, /* instance size */
        igVec2fList_GetVTable,
        &igVec2fList_InitFields_0018a430[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}
