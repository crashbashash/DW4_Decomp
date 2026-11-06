/* 0x001e4830 igMatrixStack_Register: registers class igMatrixStack with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igMatrixStack_GetVTable[];
extern char thunk_igMatrixStack_GetMetaObject[];
extern char igDataList_Register[];
extern char igMatrixStack_className[];
extern char g_igMatrixStack_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
extern int igMatrixStack_InitFields_001e48b0[4];
void igMatrixStack_Register(void) {
    /* Once-only static-init guard for this unit: the first call sets a gp-relative flag byte and
     * (in some units) chains the RunStaticInit thunks of related classes; per its asm, not a registrar. */
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMatrixStack_metaObject,   /* published MetaObject slot */
        igDataList_Register,                   /* base class registrar */
        igDataList_GetPublishedMetaObject,     /* base class MetaObject accessor */
        thunk_igMatrixStack_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igMatrixStack_className,    /* class name */
        0x14,                                  /* instance size */
        igMatrixStack_GetVTable,               /* vtable getter */
        &igMatrixStack_InitFields_001e48b0[0], /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
