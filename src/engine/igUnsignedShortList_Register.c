/* igUnsignedShortList_Register: static-init registration of igUnsignedShortList (an igDataList of
 * unsigned 16-bit elements) with the object system. The igMetaObject_RegisterClass arguments are
 * laid out per docs/engine/reflection-metadata.md section 1; names from data/reflection.json.
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
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igUnsignedShortList_metaObject,   /* published MetaObject slot */
        igDataList_Register,                         /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,           /* base class MetaObject accessor */
        thunk_igUnsignedShortList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igUnsignedShortList_className,    /* class name */
        0x14,                                        /* instance size */
        igUnsignedShortList_GetVTable,               /* vtable getter */
        &igUnsignedShortList_InitFields_002ca1a0[0], /* field adder (class InitFields) */
        0,                                           /* extra callback item */
        0                                            /* callback list */
    );
}
