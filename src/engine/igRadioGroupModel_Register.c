/* 0x0044d2c0 igRadioGroupModel_Register: registers class igRadioGroupModel with the object system, derived from igModel.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRadioGroupModel_GetVTable[];
extern char thunk_igRadioGroupModel_GetMetaObject[];
extern char igModel_GetPublishedMetaObject[];
extern char igModel_Register[];
extern char igRadioGroupModel_className[];
extern char g_igRadioGroupModel_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igRadioGroupModel_InitFields();

void igRadioGroupModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRadioGroupModel_metaObject, /* published MetaObject slot */
        igModel_Register,                        /* base class registrar */
        igModel_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igRadioGroupModel_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igRadioGroupModel_className,  /* class name */
        0x10,                                    /* instance size */
        igRadioGroupModel_GetVTable,             /* vtable getter */
        &igRadioGroupModel_InitFields,           /* field adder */
        0,                                       /* extra callback item */
        0                                        /* callback list */
    );
}
