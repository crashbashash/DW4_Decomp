/* 0x002bcaa0 igPluginRepository_Register: registers class igPluginRepository with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject_0014a6e0[];
extern char igPluginRepository_GetVTable[];
extern char thunk_igPluginRepository_GetMetaObject[];
extern char igNamedObject_Register[];
extern char s_igPluginRepository_className_004f63c0[];
extern char g_igPluginRepository_metaObject_00585af0[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igPluginRepository_InitFields();

void igPluginRepository_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPluginRepository_metaObject_00585af0,      /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject_0014a6e0, /* base class MetaObject accessor */
        thunk_igPluginRepository_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igPluginRepository_className_004f63c0,       /* class name */
        0x14,                                          /* instance size */
        igPluginRepository_GetVTable,                  /* vtable getter */
        &igPluginRepository_InitFields,                /* field adder */
        0,                                             /* extra callback item */
        0                                              /* callback list */
    );
}
