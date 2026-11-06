/* 0x0014b720 igVertexArray1_1_Register: registers class igVertexArray1_1 with the object system, derived from igVertexArray.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char thunk_igVertexArray1_1_GetMetaObject[];
extern char igVertexArray_GetPublishedMetaObject[];
extern char igVertexArray_Register[];
extern char g_igVertexArray1_1_callbackList[];
extern char igVertexArray1_1_className[];
extern char g_igVertexArray1_1_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int thunk_FUN_0015e010[4];
int igVertexArray1_1_InitFields();

void igVertexArray1_1_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVertexArray1_1_metaObject,        /* published MetaObject slot */
        igVertexArray_Register,                        /* base class registrar */
        igVertexArray_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igVertexArray1_1_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igVertexArray1_1_className,         /* class name */
        0x30,                                          /* instance size */
        0,                                             /* vtable getter */
        &igVertexArray1_1_InitFields,                  /* field adder */
        thunk_FUN_0015e010,                            /* extra callback item */
        g_igVertexArray1_1_callbackList       /* callback list */
    );
}
