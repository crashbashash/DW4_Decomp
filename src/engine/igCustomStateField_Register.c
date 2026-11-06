/* 0x0014ece0 igCustomStateField_Register: registers class igCustomStateField with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject[];
extern char igCustomStateField_GetVTable[];
extern char thunk_igCustomStateField_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igCustomStateField_callbackList[];
extern char igCustomStateField_className[];
extern char g_igCustomStateField_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igCustomStateField_InitFields();

void igCustomStateField_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCustomStateField_metaObject,      /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igCustomStateField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igCustomStateField_className,       /* class name */
        0x14,                                          /* instance size */
        igCustomStateField_GetVTable,                  /* vtable getter */
        &igCustomStateField_InitFields,                /* field adder */
        0,                                             /* extra callback item */
        g_igCustomStateField_callbackList     /* callback list */
    );
}
