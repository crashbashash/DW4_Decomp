/* 0x001e5cf0 igBoolObject_Register: registers class igBoolObject with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igBoolObject_GetVTable[];
extern char thunk_igBoolObject_GetMetaObject[];
extern char igObject_Register[];
extern char igBoolObject_className[];
extern char g_igBoolObject_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igBoolObject_InitFields();

void igBoolObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBoolObject_metaObject,    /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igBoolObject_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        igBoolObject_className,     /* class name */
        0xC,                                   /* instance size */
        igBoolObject_GetVTable,                /* vtable getter */
        &igBoolObject_InitFields,              /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
