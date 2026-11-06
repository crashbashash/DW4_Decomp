/* 0x00225eb0 igOptConfiguration_Register: registers class igOptConfiguration with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igOptConfiguration_GetVTable[];
extern char thunk_igOptConfiguration_GetMetaObject[];
extern char igObject_Register[];
extern char igOptConfiguration_className[];
extern char g_igOptConfiguration_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igOptConfiguration_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igOptConfiguration_metaObject, /* published MetaObject slot */
        igObject_Register,                        /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,    /* base class MetaObject accessor */
        thunk_igOptConfiguration_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igOptConfiguration_className,  /* class name */
        8,                                        /* instance size */
        igOptConfiguration_GetVTable,             /* vtable getter */
        0,                                        /* field adder */
        0,                                        /* extra callback item */
        0                                         /* callback list */
    );
}
