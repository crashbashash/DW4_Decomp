/* 0x0014af90 igVertexStream_Register: registers class igVertexStream with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject_0014a6e0[];
extern char igVertexStream_GetVTable[];
extern char thunk_igVertexStream_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igVertexStream_callbackList_004885a0[];
extern char s_igVertexStream_className_004dbb58[];
extern char g_igVertexStream_metaObject_0055fa10[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igVertexStream_InitFields();

void igVertexStream_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVertexStream_metaObject_0055fa10,          /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject_0014a6e0, /* base class MetaObject accessor */
        thunk_igVertexStream_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        s_igVertexStream_className_004dbb58,           /* class name */
        0x24,                                          /* instance size */
        igVertexStream_GetVTable,                      /* vtable getter */
        &igVertexStream_InitFields,                    /* field adder */
        0,                                             /* extra callback item */
        g_igVertexStream_callbackList_004885a0         /* callback list */
    );
}
