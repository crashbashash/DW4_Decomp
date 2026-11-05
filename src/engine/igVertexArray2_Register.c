/* 0x0014ab80 igVertexArray2_Register: registers class igVertexArray2 with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject_0014a6e0[];
extern char igVertexArray2_GetVTable[];
extern char thunk_igVertexArray2_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igVertexArray2_callbackList_00488510[];
extern char s_igVertexArray2_className_004db9d8[];
extern char g_igVertexArray2_metaObject_0055f9e0[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igVertexArray2_InitFields();

void igVertexArray2_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVertexArray2_metaObject_0055f9e0,          /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject_0014a6e0, /* base class MetaObject accessor */
        thunk_igVertexArray2_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        s_igVertexArray2_className_004db9d8,           /* class name */
        0x18,                                          /* instance size */
        igVertexArray2_GetVTable,                      /* vtable getter */
        &igVertexArray2_InitFields,                    /* field adder */
        0,                                             /* extra callback item */
        g_igVertexArray2_callbackList_00488510         /* callback list */
    );
}
