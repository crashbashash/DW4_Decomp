/* 0x002cbbc0 igContext_Register: registers class igContext with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igContext_GetMetaObject[];
extern char igObject_Register[];
extern char g_igContext_callbackList[];
extern char igContext_className[];
extern char g_igContext_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igContext_InitFields();

void igContext_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igContext_metaObject,       /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igContext_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igContext_className,        /* class name */
        0x14,                                  /* instance size */
        0,                                     /* vtable getter */
        &igContext_InitFields,                 /* field adder */
        0,                                     /* extra callback item */
        g_igContext_callbackList      /* callback list */
    );
}
