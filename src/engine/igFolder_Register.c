/* 0x002c44d0 igFolder_Register: registers class igFolder with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igFolder_GetVTable[];
extern char thunk_igFolder_GetMetaObject[];
extern char igObject_Register[];
extern char igFolder_className[];
extern char g_igFolder_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igFolder_InitFields();

void igFolder_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFolder_metaObject,        /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igFolder_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igFolder_className,         /* class name */
        0xC,                                   /* instance size */
        igFolder_GetVTable,                    /* vtable getter */
        &igFolder_InitFields,                  /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
