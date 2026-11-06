/* 0x001a6460 igAppearance_Register: registers class igAppearance with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject[];
extern char igAppearance_GetVTable[];
extern char thunk_igAppearance_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igAppearance_callbackList[];
extern char igAppearance_className[];
extern char g_igAppearance_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igAppearance_InitFields();

void igAppearance_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAppearance_metaObject,            /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igAppearance_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        igAppearance_className,             /* class name */
        0x20,                                          /* instance size */
        igAppearance_GetVTable,                        /* vtable getter */
        &igAppearance_InitFields,                      /* field adder */
        0,                                             /* extra callback item */
        g_igAppearance_callbackList           /* callback list */
    );
}
