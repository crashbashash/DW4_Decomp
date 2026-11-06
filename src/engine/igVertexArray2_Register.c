/* 0x0014ab80 igVertexArray2_Register: registers class igVertexArray2 with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject[];
extern char igVertexArray2_GetVTable[];
extern char thunk_igVertexArray2_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igVertexArray2_callbackList[];
extern char igVertexArray2_className[];
extern char g_igVertexArray2_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igVertexArray2_InitFields();

void igVertexArray2_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVertexArray2_metaObject,          /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igVertexArray2_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        igVertexArray2_className,           /* class name */
        0x18,                                          /* instance size */
        igVertexArray2_GetVTable,                      /* vtable getter */
        &igVertexArray2_InitFields,                    /* field adder */
        0,                                             /* extra callback item */
        g_igVertexArray2_callbackList         /* callback list */
    );
}
