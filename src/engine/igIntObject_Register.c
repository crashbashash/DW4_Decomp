/* 0x001e4ed0 igIntObject_Register: registers class igIntObject with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igIntObject_GetVTable[];
extern char thunk_igIntObject_GetMetaObject[];
extern char igObject_Register[];
extern char igIntObject_className[];
extern char g_igIntObject_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igIntObject_InitFields();

void igIntObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIntObject_metaObject,     /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igIntObject_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igIntObject_className,      /* class name */
        0xC,                                   /* instance size */
        igIntObject_GetVTable,                 /* vtable getter */
        &igIntObject_InitFields,               /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
