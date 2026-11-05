/* 0x002cff40 igPsx2IopRpcConnection_Register: registers class igPsx2IopRpcConnection with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igPsx2IopRpcConnection_GetVTable[];
extern char thunk_igPsx2IopRpcConnection_GetMetaObject[];
extern char igObject_Register[];
extern char s_igPsx2IopRpcConnection_className_004f8fc0[];
extern char g_igPsx2IopRpcConnection_metaObject_00586d48[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igPsx2IopRpcConnection_InitFields();

void igPsx2IopRpcConnection_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2IopRpcConnection_metaObject_00586d48, /* published MetaObject slot */
        igObject_Register,                            /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,        /* base class MetaObject accessor */
        thunk_igPsx2IopRpcConnection_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2IopRpcConnection_className_004f8fc0,  /* class name */
        0x14,                                         /* instance size */
        igPsx2IopRpcConnection_GetVTable,             /* vtable getter */
        &igPsx2IopRpcConnection_InitFields,           /* field adder */
        0,                                            /* extra callback item */
        0                                             /* callback list */
    );
}
