/* 0x0014b720 igVertexArray1_1_Register: registers class igVertexArray1_1 with the object system, derived from igVertexArray.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char thunk_igVertexArray1_1_GetMetaObject[];
extern char igVertexArray_GetPublishedMetaObject_0014b7b0[];
extern char igVertexArray_Register[];
extern char g_igVertexArray1_1_callbackList_00488740[];
extern char s_igVertexArray1_1_className_004dbdd0[];
extern char g_igVertexArray1_1_metaObject_0055fa90[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int thunk_FUN_0015e010[4];
int igVertexArray1_1_InitFields();

void igVertexArray1_1_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVertexArray1_1_metaObject_0055fa90,        /* published MetaObject slot */
        igVertexArray_Register,                        /* base class registrar */
        igVertexArray_GetPublishedMetaObject_0014b7b0, /* base class MetaObject accessor */
        thunk_igVertexArray1_1_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        s_igVertexArray1_1_className_004dbdd0,         /* class name */
        0x30,                                          /* instance size */
        0,                                             /* vtable getter */
        &igVertexArray1_1_InitFields,                  /* field adder */
        thunk_FUN_0015e010,                            /* extra callback item */
        g_igVertexArray1_1_callbackList_00488740       /* callback list */
    );
}
