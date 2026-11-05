/* 0x0013b120 igAttr_Register: registers class igAttr with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igAttr_GetMetaObject[];
extern char FUN_0013b240[];
extern char igObject_Register[];
extern char s_igAttr_className_004d5d68[];
extern char g_igAttr_metaObject_0055f468[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igAttr_InitFields();

void igAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAttr_metaObject_0055f468,          /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igAttr_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        s_igAttr_className_004d5d68,           /* class name */
        0xC,                                   /* instance size */
        0,                                     /* vtable getter */
        &igAttr_InitFields,                    /* field adder */
        FUN_0013b240,                          /* extra callback item */
        0                                      /* callback list */
    );
}
