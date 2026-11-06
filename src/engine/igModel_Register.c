/* 0x0044d710 igModel_Register: registers class igModel with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igModel_GetVTable[];
extern char thunk_igModel_GetMetaObject[];
extern char g_igModel_callbackList[];
extern char igModel_className[];
extern char g_igModel_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igModel_InitFields();

void igModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igModel_metaObject,         /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igModel_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        igModel_className,          /* class name */
        0xC,                                   /* instance size */
        igModel_GetVTable,                     /* vtable getter */
        &igModel_InitFields,                   /* field adder */
        0,                                     /* extra callback item */
        g_igModel_callbackList        /* callback list */
    );
}
