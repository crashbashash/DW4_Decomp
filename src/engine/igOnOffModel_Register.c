/* 0x0044d4e0 igOnOffModel_Register: registers class igOnOffModel with the object system, derived from igGuiComponentModel.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGuiComponentModel_GetPublishedMetaObject[];
extern char igOnOffModel_GetVTable[];
extern char thunk_igOnOffModel_GetMetaObject[];
extern char igGuiComponentModel_Register[];
extern char igOnOffModel_className[];
extern char g_igOnOffModel_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igOnOffModel_InitFields();

void igOnOffModel_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igOnOffModel_metaObject,                  /* published MetaObject slot */
        igGuiComponentModel_Register,                        /* base class registrar */
        igGuiComponentModel_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igOnOffModel_GetMetaObject,                    /* own MetaObject accessor (stored at +0x54) */
        igOnOffModel_className,                   /* class name */
        0x28,                                                /* instance size */
        igOnOffModel_GetVTable,                              /* vtable getter */
        &igOnOffModel_InitFields,                            /* field adder */
        0,                                                   /* extra callback item */
        0                                                    /* callback list */
    );
}
