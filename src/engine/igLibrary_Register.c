/* 0x002c2580 igLibrary_Register: registers class igLibrary with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igLibrary_GetMetaObject[];
extern char igObject_Register[];
extern char igLibrary_className[];
extern char g_igLibrary_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igLibrary_InitFields();

void igLibrary_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLibrary_metaObject,       /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igLibrary_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igLibrary_className,        /* class name */
        0xC,                                   /* instance size */
        0,                                     /* vtable getter */
        &igLibrary_InitFields,                 /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
