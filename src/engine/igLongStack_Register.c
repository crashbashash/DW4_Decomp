/* 0x001e4100 igLongStack_Register: registers class igLongStack with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igLongStack_GetVTable[];
extern char thunk_igLongStack_GetMetaObject[];
extern char igDataList_Register[];
extern char igLongStack_className[];
extern char g_igLongStack_metaObject[];
int GpFlag_SetOnce_001e3ff0();
int igMetaObject_RegisterClass();
extern int igLongStack_InitFields_001e4180[4];
void igLongStack_Register(void) {
    /* Once-only static-init guard for this unit: the first call sets a gp-relative flag byte and
     * (in some units) chains the RunStaticInit thunks of related classes; per its asm, not a registrar. */
    GpFlag_SetOnce_001e3ff0();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLongStack_metaObject,   /* published MetaObject slot */
        igDataList_Register,                 /* base class registrar */
        igDataList_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igLongStack_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igLongStack_className,    /* class name */
        0x14,                                /* instance size */
        igLongStack_GetVTable,               /* vtable getter */
        &igLongStack_InitFields_001e4180[0], /* field adder */
        0,                                   /* extra callback item */
        0                                    /* callback list */
    );
}
