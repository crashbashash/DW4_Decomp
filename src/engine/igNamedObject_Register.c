/* 0x002be3e0 igNamedObject_Register: registers class igNamedObject with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igNamedObject_GetVTable[];
extern char thunk_igNamedObject_GetMetaObject[];
extern char igObject_Register[];
extern char s_igNamedObject_className_004f6598[];
extern char g_igNamedObject_metaObject_00585bd8[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igNamedObject_InitFields();

void igNamedObject_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNamedObject_metaObject_00585bd8,   /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igNamedObject_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igNamedObject_className_004f6598,    /* class name */
        0xC,                                   /* instance size */
        igNamedObject_GetVTable,               /* vtable getter */
        &igNamedObject_InitFields,             /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
