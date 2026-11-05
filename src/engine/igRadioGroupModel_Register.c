/* 0x0044d2c0 igRadioGroupModel_Register: registers class igRadioGroupModel with the object system, derived from igModel.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRadioGroupModel_GetVTable[];
extern char thunk_igRadioGroupModel_GetMetaObject[];
extern char igModel_GetPublishedMetaObject_0044d340[];
extern char igModel_Register[];
extern char s_igRadioGroupModel_className_0051ded0[];
extern char g_igRadioGroupModel_metaObject_0058c278[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igRadioGroupModel_InitFields();

void igRadioGroupModel_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRadioGroupModel_metaObject_0058c278, /* published MetaObject slot */
        igModel_Register,                        /* base class registrar */
        igModel_GetPublishedMetaObject_0044d340, /* base class MetaObject accessor */
        thunk_igRadioGroupModel_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igRadioGroupModel_className_0051ded0,  /* class name */
        0x10,                                    /* instance size */
        igRadioGroupModel_GetVTable,             /* vtable getter */
        &igRadioGroupModel_InitFields,           /* field adder */
        0,                                       /* extra callback item */
        0                                        /* callback list */
    );
}
