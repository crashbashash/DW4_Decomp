/* Static-init registration of igUnsignedCharList (an igDataList of unsigned 8-bit elements).
 * FUN_002b5d50 is the set-once latch every registrar of this group calls first (a gp byte flag
 * guards a few shared one-time registrations). */
extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igUnsignedCharList_GetVTable[];
extern char thunk_igUnsignedCharList_GetMetaObject[];
extern char igUnsignedCharList_className[];
extern char g_igUnsignedCharList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igUnsignedCharList_InitFields_002c9b10[4];
void igUnsignedCharList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igUnsignedCharList_metaObject,
        igDataList_Register,                        /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        thunk_igUnsignedCharList_GetMetaObject,
        igUnsignedCharList_className,
        0x14, /* instance size */
        igUnsignedCharList_GetVTable,
        &igUnsignedCharList_InitFields_002c9b10[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}
