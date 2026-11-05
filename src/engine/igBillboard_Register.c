/* 0x001a5060 igBillboard_Register: registers class igBillboard with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject_001943a0[];
extern char igGroup_Register[];
extern char igBillboard_GetVTable[];
extern char thunk_igBillboard_GetMetaObject[];
extern char g_igBillboard_callbackList_0048cbb8[];
extern char s_igBillboard_className_004e3470[];
extern char g_igBillboard_metaObject_00561f68[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igBillboard_InitFields();

void igBillboard_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBillboard_metaObject_00561f68,       /* published MetaObject slot */
        igGroup_Register,                        /* base class registrar */
        igGroup_GetPublishedMetaObject_001943a0, /* base class MetaObject accessor */
        thunk_igBillboard_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igBillboard_className_004e3470,        /* class name */
        0x40,                                    /* instance size */
        igBillboard_GetVTable,                   /* vtable getter */
        &igBillboard_InitFields,                 /* field adder */
        0,                                       /* extra callback item */
        g_igBillboard_callbackList_0048cbb8      /* callback list */
    );
}
