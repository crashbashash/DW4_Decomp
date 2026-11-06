/* 0x002c5ef0 igErrorHandler_Register: registers class igErrorHandler with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igErrorHandler_GetVTable[];
extern char thunk_igErrorHandler_GetMetaObject[];
extern char thunk_thunk_FUN_002dca20[];
extern char igObject_Register[];
extern char igErrorHandler_className[];
extern char g_igErrorHandler_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002c5f80(void);
void igErrorHandler_Register(void) {
    FUN_002b5d50();  /* set-once guard that first runs the sibling registrars it chains to (asm/FUN_002b5d50.s) */
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igErrorHandler_metaObject,  /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igErrorHandler_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        igErrorHandler_className,   /* class name */
        8,                                     /* instance size */
        igErrorHandler_GetVTable,              /* vtable getter */
        FUN_002c5f80,                      /* field adder */
        thunk_thunk_FUN_002dca20,              /* static-initializer callback item (appended on fresh configuration) */
        0                                      /* 0-terminated dependency-callback list */
    );
}
