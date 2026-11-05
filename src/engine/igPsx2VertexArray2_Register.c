/* 0x001522d0 igPsx2VertexArray2_Register: registers class igPsx2VertexArray2 with the object system, derived from igVertexArray2.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVertexArray2_Register[];
extern char thunk_igPsx2VertexArray2_GetMetaObject_0014acf0[];
extern char igPsx2VertexArray2_GetVTable[];
extern char igVertexArray2_GetPublishedMetaObject_00152340[];
extern char s_igPsx2VertexArray2_className_004ddf50[];
extern char g_igPsx2VertexArray2_metaObject_00560478[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int igPsx2VertexArray2_InitFields_00152350[4];
void igPsx2VertexArray2_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2VertexArray2_metaObject_00560478,        /* published MetaObject slot */
        igVertexArray2_Register,                         /* base class registrar */
        igVertexArray2_GetPublishedMetaObject_00152340,  /* base class MetaObject accessor */
        thunk_igPsx2VertexArray2_GetMetaObject_0014acf0, /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2VertexArray2_className_004ddf50,         /* class name */
        0x18,                                            /* instance size */
        igPsx2VertexArray2_GetVTable,                    /* vtable getter */
        &igPsx2VertexArray2_InitFields_00152350[0],      /* field adder (post_init in data/reflection.json) */
        0,                                               /* extra callback-vector item (none; docs/engine/reflection-registration.md) */
        0                                                /* zero-terminated callback-vector item list (none) */
    );
}
