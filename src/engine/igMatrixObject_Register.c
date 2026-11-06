/* 0x001e4d40 igMatrixObject_Register: registers class igMatrixObject with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igMatrixObject_GetVTable[];
extern char thunk_igMatrixObject_GetMetaObject[];
extern char igObject_Register[];
extern char igMatrixObject_className[];
extern char g_igMatrixObject_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igMatrixObject_InitFields();

void igMatrixObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMatrixObject_metaObject,  /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igMatrixObject_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        igMatrixObject_className,   /* class name */
        0x48,                                  /* instance size */
        igMatrixObject_GetVTable,              /* vtable getter */
        &igMatrixObject_InitFields,            /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
