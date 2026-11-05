/* 0x00143020 igAudioContext_Register: registers class igAudioContext with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igAudioContext_GetMetaObject[];
extern char igObject_Register[];
extern char s_igAudioContext_className_004d5e68[];
extern char g_igAudioContext_metaObject_0055f540[];
int GpFlag_SetOnce_00142f10();
int igMetaObject_RegisterClass();
int igAudioContext_InitFields();

void igAudioContext_Register(void) {
    GpFlag_SetOnce_00142f10();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAudioContext_metaObject_0055f540,  /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igAudioContext_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        s_igAudioContext_className_004d5e68,   /* class name */
        0xC,                                   /* instance size */
        0,                                     /* vtable getter */
        &igAudioContext_InitFields,            /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
