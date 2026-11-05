/* 0x0014a650 igVertexArray2Helper_Register: registers class igVertexArray2Helper with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVertexArray2Helper_GetVTable[];
extern char thunk_igVertexArray2Helper_GetMetaObject[];
extern char igNamedObject_GetPublishedMetaObject_0014a6e0[];
extern char igNamedObject_Register[];
extern char g_igVertexArray2Helper_callbackList_004884e8[];
extern char s_igVertexArray2Helper_className_004db9b0[];
extern char g_igVertexArray2Helper_metaObject_0055f9d0[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igVertexArray2Helper_InitFields();

void igVertexArray2Helper_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVertexArray2Helper_metaObject_0055f9d0,    /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject_0014a6e0, /* base class MetaObject accessor */
        thunk_igVertexArray2Helper_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        s_igVertexArray2Helper_className_004db9b0,     /* class name */
        0x10,                                          /* instance size */
        igVertexArray2Helper_GetVTable,                /* vtable getter */
        &igVertexArray2Helper_InitFields,              /* field adder */
        0,                                             /* extra callback item */
        g_igVertexArray2Helper_callbackList_004884e8   /* callback list */
    );
}
