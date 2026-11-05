/* 0x001525f0 igPsx2VertexArray1_1_Register: registers class igPsx2VertexArray1_1 with the object system, derived from igVertexArray1_1.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVertexArray1_1_Register[];
extern char thunk_igPsx2VertexArray1_1_GetMetaObject[];
extern char igPsx2VertexArray1_1_GetVTable[];
extern char igVertexArray1_1_GetPublishedMetaObject_00152670[];
extern char g_igPsx2VertexArray1_1_callbackList_00489d18[];
extern char s_igPsx2VertexArray1_1_className_004ddf70[];
extern char g_igPsx2VertexArray1_1_metaObject_00560480[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2VertexArray1_1_InitFields();

void igPsx2VertexArray1_1_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                                /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2VertexArray1_1_metaObject_00560480,       /* published MetaObject slot */
        igVertexArray1_1_Register,                        /* base class registrar */
        igVertexArray1_1_GetPublishedMetaObject_00152670, /* base class MetaObject accessor */
        thunk_igPsx2VertexArray1_1_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2VertexArray1_1_className_004ddf70,        /* class name */
        0x90,                                             /* instance size */
        igPsx2VertexArray1_1_GetVTable,                   /* vtable getter */
        &igPsx2VertexArray1_1_InitFields,                 /* field adder */
        0,                                                /* extra callback item */
        g_igPsx2VertexArray1_1_callbackList_00489d18      /* callback list */
    );
}
