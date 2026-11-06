/* 0x002cea90 igProgramFile_Register: registers class igProgramFile with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igProgramFile_GetVTable[];
extern char thunk_igProgramFile_GetMetaObject[];
extern char igObject_Register[];
extern char g_igProgramFile_callbackList[];
extern char igProgramFile_className[];
extern char g_igProgramFile_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igProgramFile_InitFields();

void igProgramFile_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igProgramFile_metaObject,   /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igProgramFile_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igProgramFile_className,    /* class name */
        0x10,                                  /* instance size */
        igProgramFile_GetVTable,               /* vtable getter */
        &igProgramFile_InitFields,             /* field adder */
        0,                                     /* extra callback item */
        g_igProgramFile_callbackList  /* callback list */
    );
}
