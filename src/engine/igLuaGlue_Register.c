/* 0x0023c7b0 igLuaGlue_Register: registers class igLuaGlue with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igLuaGlue_GetVTable[];
extern char thunk_igLuaGlue_GetMetaObject[];
extern char igObject_Register[];
extern char igLuaGlue_className[];
extern char g_igLuaGlue_metaObject[];
int LuaLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igLuaGlue_Register(void) {
    LuaLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLuaGlue_metaObject,       /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igLuaGlue_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igLuaGlue_className,        /* class name */
        8,                                     /* instance size */
        igLuaGlue_GetVTable,                   /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
