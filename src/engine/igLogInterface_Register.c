/* 0x002266d0 igLogInterface_Register: registers class igLogInterface with the object system, derived from igInterface.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInterface_GetPublishedMetaObject[];
extern char igLogInterface_GetVTable[];
extern char thunk_igLogInterface_GetMetaObject[];
extern char igInterface_Register[];
extern char igLogInterface_className[];
extern char g_igLogInterface_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igLogInterface_InitFields();

void igLogInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLogInterface_metaObject,        /* published MetaObject slot */
        igInterface_Register,                        /* base class registrar */
        igInterface_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igLogInterface_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igLogInterface_className,         /* class name */
        0x24,                                        /* instance size */
        igLogInterface_GetVTable,                    /* vtable getter */
        &igLogInterface_InitFields,                  /* field adder */
        0,                                           /* extra callback item */
        0                                            /* callback list */
    );
}
