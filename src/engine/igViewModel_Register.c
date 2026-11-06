/* 0x0045d5d0 igViewModel_Register: registers class igViewModel with the object system, derived from igModel.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igModel_GetPublishedMetaObject[];
extern char igModel_Register[];
extern char igViewModel_GetVTable[];
extern char thunk_igViewModel_GetMetaObject[];
extern char igViewModel_className[];
extern char g_igViewModel_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igViewModel_InitFields();

void igViewModel_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewModel_metaObject,       /* published MetaObject slot */
        igModel_Register,                        /* base class registrar */
        igModel_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igViewModel_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igViewModel_className,        /* class name */
        0xB0,                                    /* instance size */
        igViewModel_GetVTable,                   /* vtable getter */
        &igViewModel_InitFields,                 /* field adder */
        0,                                       /* extra callback item */
        0                                        /* callback list */
    );
}
