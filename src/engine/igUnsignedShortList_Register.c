/* Static-init registration of igUnsignedShortList (an igDataList of unsigned 16-bit elements).
 * FUN_002b5d50 is the set-once latch every registrar of this group calls first (a gp byte flag
 * guards a few shared one-time registrations). */
extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igUnsignedShortList_GetVTable[];
extern char thunk_igUnsignedShortList_GetMetaObject[];
extern char igUnsignedShortList_className[];
extern char g_igUnsignedShortList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igUnsignedShortList_InitFields_002ca1a0[4];
void igUnsignedShortList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igUnsignedShortList_metaObject,
        igDataList_Register,                         /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        thunk_igUnsignedShortList_GetMetaObject,
        igUnsignedShortList_className,
        0x14, /* instance size */
        igUnsignedShortList_GetVTable,
        &igUnsignedShortList_InitFields_002ca1a0[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}
