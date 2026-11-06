/* 0x00152060 igPsx2VertexStream_Register: registers class igPsx2VertexStream with the object system, derived from igVertexStream.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVertexStream_Register[];
extern char thunk_igPsx2VertexStream_GetMetaObject[];
extern char igPsx2VertexStream_GetVTable[];
extern char igVertexStream_GetPublishedMetaObject[];
extern char thunk_FUN_0017f5a0[];
extern char igPsx2VertexStream_className[];
extern char g_igPsx2VertexStream_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2VertexStream_InitFields();

void igPsx2VertexStream_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2VertexStream_metaObject,       /* published MetaObject slot */
        igVertexStream_Register,                        /* base class registrar */
        igVertexStream_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPsx2VertexStream_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igPsx2VertexStream_className,        /* class name */
        0x90,                                           /* instance size */
        igPsx2VertexStream_GetVTable,                   /* vtable getter */
        &igPsx2VertexStream_InitFields,                 /* field adder */
        thunk_FUN_0017f5a0,                             /* extra callback item */
        0                                               /* callback list */
    );
}
