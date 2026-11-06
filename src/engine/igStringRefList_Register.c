/* Static-init registration of igStringRefList (an igDataList of string-reference elements).
 * FUN_002b5d50 is the set-once latch every registrar of this group calls first (a gp byte flag
 * guards a few shared one-time registrations). */
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
        0, /* abstract */
        g_igStringRefList_metaObject,
        igDataList_Register,                     /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        thunk_igStringRefList_GetMetaObject,
        igStringRefList_className,
        0x14, /* instance size */
        igStringRefList_GetVTable,
        &igStringRefList_InitFields_002b9290[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}
