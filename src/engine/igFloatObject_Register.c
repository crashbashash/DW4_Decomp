/* 0x001e5060 igFloatObject_Register: registers class igFloatObject with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igFloatObject_GetVTable[];
extern char thunk_igFloatObject_GetMetaObject[];
extern char igObject_Register[];
extern char igFloatObject_className[];
extern char g_igFloatObject_metaObject[];
int GpFlag_SetOnce_001e3ff0();
int igMetaObject_RegisterClass();
int igFloatObject_InitFields();

void igFloatObject_Register(void) {
    GpFlag_SetOnce_001e3ff0();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFloatObject_metaObject,   /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igFloatObject_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igFloatObject_className,    /* class name */
        0xC,                                   /* instance size */
        igFloatObject_GetVTable,               /* vtable getter */
        &igFloatObject_InitFields,             /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
