/* 0x0014d8a0 igIndexArray_Register: registers class igIndexArray with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igIndexArray_GetMetaObject[];
extern char igObject_Register[];
extern char g_igIndexArray_callbackList[];
extern char igIndexArray_className[];
extern char g_igIndexArray_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igIndexArray_InitFields();

void igIndexArray_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIndexArray_metaObject,    /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igIndexArray_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        igIndexArray_className,     /* class name */
        0x1C,                                  /* instance size */
        0,                                     /* vtable getter */
        &igIndexArray_InitFields,              /* field adder */
        0,                                     /* extra callback item */
        g_igIndexArray_callbackList   /* callback list */
    );
}
