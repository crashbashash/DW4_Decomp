/* 0x002cc970 igCallStackTable_Register: registers class igCallStackTable with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igCallStackTable_GetVTable[];
extern char thunk_igCallStackTable_GetMetaObject[];
extern char igObject_Register[];
extern char g_igCallStackTable_callbackList[];
extern char igCallStackTable_className[];
extern char g_igCallStackTable_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igCallStackTable_InitFields();

void igCallStackTable_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCallStackTable_metaObject, /* published MetaObject slot */
        igObject_Register,                      /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,  /* base class MetaObject accessor */
        thunk_igCallStackTable_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igCallStackTable_className,  /* class name */
        0x18,                                   /* instance size */
        igCallStackTable_GetVTable,             /* vtable getter */
        &igCallStackTable_InitFields,           /* field adder */
        0,                                      /* extra callback item */
        g_igCallStackTable_callbackList  /* callback list */
    );
}
