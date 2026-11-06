/* 0x0044cfd0 igRadioGroup_Register: registers class igRadioGroup with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igRadioGroup_GetVTable[];
extern char thunk_igRadioGroup_GetMetaObject[];
extern char g_igRadioGroup_callbackList[];
extern char igRadioGroup_className[];
extern char g_igRadioGroup_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igRadioGroup_InitFields();

void igRadioGroup_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRadioGroup_metaObject,    /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igRadioGroup_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        igRadioGroup_className,     /* class name */
        0x20,                                  /* instance size */
        igRadioGroup_GetVTable,                /* vtable getter */
        &igRadioGroup_InitFields,              /* field adder */
        0,                                     /* extra callback item */
        g_igRadioGroup_callbackList   /* callback list */
    );
}
