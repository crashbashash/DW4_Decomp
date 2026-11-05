/* 0x0014b510 igVertexData_Register: registers class igVertexData with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject_0014a6e0[];
extern char igVertexData_GetVTable[];
extern char thunk_igVertexData_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igVertexData_callbackList_004886b0[];
extern char s_igVertexData_className_004dbd60[];
extern char g_igVertexData_metaObject_0055fa58[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igVertexData_InitFields();

void igVertexData_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVertexData_metaObject_0055fa58,            /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject_0014a6e0, /* base class MetaObject accessor */
        thunk_igVertexData_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        s_igVertexData_className_004dbd60,             /* class name */
        0x24,                                          /* instance size */
        igVertexData_GetVTable,                        /* vtable getter */
        &igVertexData_InitFields,                      /* field adder */
        0,                                             /* extra callback item */
        g_igVertexData_callbackList_004886b0           /* callback list */
    );
}
