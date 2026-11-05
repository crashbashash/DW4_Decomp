/* 0x00225910 igCompoundList_Register: registers class igCompoundList with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igCompoundList_GetVTable[];
extern char thunk_igCompoundList_GetMetaObject[];
extern char igObject_Register[];
extern char s_igCompoundList_className_004e7980[];
extern char g_igCompoundList_metaObject_0056d840[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();
int igCompoundList_InitFields();

void igCompoundList_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCompoundList_metaObject_0056d840,  /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igCompoundList_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        s_igCompoundList_className_004e7980,   /* class name */
        0x14,                                  /* instance size */
        igCompoundList_GetVTable,              /* vtable getter */
        &igCompoundList_InitFields,            /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
