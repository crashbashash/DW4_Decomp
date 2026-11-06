/* 0x0014af90 igVertexStream_Register: registers class igVertexStream with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject[];
extern char igVertexStream_GetVTable[];
extern char thunk_igVertexStream_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igVertexStream_callbackList[];
extern char igVertexStream_className[];
extern char g_igVertexStream_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igVertexStream_InitFields();

void igVertexStream_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVertexStream_metaObject,          /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igVertexStream_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        igVertexStream_className,           /* class name */
        0x24,                                          /* instance size */
        igVertexStream_GetVTable,                      /* vtable getter */
        &igVertexStream_InitFields,                    /* field adder */
        0,                                             /* extra callback item */
        g_igVertexStream_callbackList         /* callback list */
    );
}
