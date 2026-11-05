/* 0x001e4830 igMatrixStack_Register: registers class igMatrixStack with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igMatrixStack_GetVTable[];
extern char thunk_igMatrixStack_GetMetaObject[];
extern char igDataList_Register[];
extern char s_igMatrixStack_className_004e4930[];
extern char g_igMatrixStack_metaObject_00562ba0[];
int GpFlag_SetOnce_001e3ff0();
int igMetaObject_RegisterClass();
extern int igMatrixStack_InitFields_001e48b0[4];
void igMatrixStack_Register(void) {
    /* Once-only static-init guard for this unit: the first call sets a gp-relative flag byte and
     * (in some units) chains the RunStaticInit thunks of related classes; per its asm, not a registrar. */
    GpFlag_SetOnce_001e3ff0();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMatrixStack_metaObject_00562ba0,   /* published MetaObject slot */
        igDataList_Register,                   /* base class registrar */
        igDataList_GetPublishedMetaObject,     /* base class MetaObject accessor */
        thunk_igMatrixStack_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igMatrixStack_className_004e4930,    /* class name */
        0x14,                                  /* instance size */
        igMatrixStack_GetVTable,               /* vtable getter */
        &igMatrixStack_InitFields_001e48b0[0], /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
