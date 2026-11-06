/* 0x0014fb80 igClut_Register: registers class igClut with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igClut_GetVTable[];
extern char thunk_igClut_GetMetaObject[];
extern char igObject_Register[];
extern char igClut_className[];
extern char g_igClut_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igClut_InitFields();

void igClut_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igClut_metaObject,          /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igClut_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        igClut_className,           /* class name */
        0x20,                                  /* instance size */
        igClut_GetVTable,                      /* vtable getter */
        &igClut_InitFields,                    /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
