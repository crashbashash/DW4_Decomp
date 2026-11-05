/* 0x0014ba30 igVertexArray_Register: registers class igVertexArray with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igVertexArray_GetMetaObject[];
extern char igObject_Register[];
extern char s_igVertexArray_className_004dbe48[];
extern char g_igVertexArray_metaObject_0055fac8[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igVertexArray_InitFields();

void igVertexArray_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVertexArray_metaObject_0055fac8,   /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igVertexArray_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igVertexArray_className_004dbe48,    /* class name */
        0x18,                                  /* instance size */
        0,                                     /* vtable getter */
        &igVertexArray_InitFields,             /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
