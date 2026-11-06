/* Static-init registration of igShortList (an igDataList of signed 16-bit elements). FUN_002b5d50
 * is the set-once latch every registrar of this group calls first (a gp byte flag guards a few
 * shared one-time registrations). */
extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igShortList_GetVTable[];
extern char thunk_igShortList_GetMetaObject[];
extern char igShortList_className[];
extern char g_igShortList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igShortList_InitFields_002c9f30[4];
void igShortList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igShortList_metaObject,
        igDataList_Register,                 /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        thunk_igShortList_GetMetaObject,
        igShortList_className,
        0x14, /* instance size */
        igShortList_GetVTable,
        &igShortList_InitFields_002c9f30[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}
