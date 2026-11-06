/* Static-init registration of igUnsignedIntList (an igDataList of unsigned 32-bit elements).
 * FUN_002b5d50 is the set-once latch every registrar of this group calls first (a gp byte flag
 * guards a few shared one-time registrations). */
extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igUnsignedIntList_GetVTable[];
extern char thunk_igUnsignedIntList_GetMetaObject[];
extern char igUnsignedIntList_className[];
extern char g_igUnsignedIntList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igUnsignedIntList_InitFields_002ca5c0[4];
void igUnsignedIntList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igUnsignedIntList_metaObject,
        igDataList_Register,                       /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        thunk_igUnsignedIntList_GetMetaObject,
        igUnsignedIntList_className,
        0x14, /* instance size */
        igUnsignedIntList_GetVTable,
        &igUnsignedIntList_InitFields_002ca5c0[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}
