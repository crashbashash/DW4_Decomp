/* 0x002c2340 igLibraryLoader_Register: registers class igLibraryLoader with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igLibraryLoader_GetMetaObject[];
extern char igObject_Register[];
extern char igLibraryLoader_className[];
extern char g_igLibraryLoader_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igLibraryLoader_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLibraryLoader_metaObject, /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igLibraryLoader_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igLibraryLoader_className,  /* class name */
        8,                                     /* instance size */
        0,                                     /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
