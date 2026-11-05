/* 0x0019d720 igLod_Register: registers class igLod with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject_001943a0[];
extern char igLod_GetVTable[];
extern char thunk_igLod_GetMetaObject[];
extern char igGroup_Register[];
extern char g_igLod_callbackList_0048bcf8[];
extern char s_igLod_className_004e2430[];
extern char g_igLod_metaObject_00561898[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igLod_InitFields();

void igLod_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLod_metaObject_00561898,             /* published MetaObject slot */
        igGroup_Register,                        /* base class registrar */
        igGroup_GetPublishedMetaObject_001943a0, /* base class MetaObject accessor */
        thunk_igLod_GetMetaObject,               /* own MetaObject accessor (stored at +0x54) */
        s_igLod_className_004e2430,              /* class name */
        0x44,                                    /* instance size */
        igLod_GetVTable,                         /* vtable getter */
        &igLod_InitFields,                       /* field adder */
        0,                                       /* extra callback item */
        g_igLod_callbackList_0048bcf8            /* callback list */
    );
}
