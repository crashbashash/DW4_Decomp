/* 0x00231710 igMessage_Register: registers class igMessage with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igMessage_GetVTable[];
extern char thunk_igMessage_GetMetaObject[];
extern char igObject_Register[];
extern char s_igMessage_className_004e8428[];
extern char g_igMessage_metaObject_0056dad8[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();

void igMessage_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMessage_metaObject_0056dad8,       /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igMessage_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igMessage_className_004e8428,        /* class name */
        8,                                     /* instance size */
        igMessage_GetVTable,                   /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
