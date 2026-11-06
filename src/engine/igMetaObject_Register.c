/* 0x002be770 igMetaObject_Register: registers class igMetaObject with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igMetaObject_GetVTable[];
extern char thunk_igMetaObject_GetMetaObject[];
extern char igObject_Register[];
extern char g_igMetaObject_callbackList[];
extern char igMetaObject_className[];
extern char g_igMetaObject_metaObject[];
int igMetaObject_RegisterClass();
int igMetaObject_InitFields();

void igMetaObject_Register(void) {
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMetaObject_metaObject,    /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igMetaObject_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        igMetaObject_className,     /* class name */
        0x64,                                  /* instance size */
        igMetaObject_GetVTable,                /* vtable getter */
        &igMetaObject_InitFields,              /* field adder */
        0,                                     /* extra callback item */
        g_igMetaObject_callbackList   /* callback list */
    );
}
