/* 0x00226a20 igLockInterface_Register: registers class igLockInterface with the object system, derived from igInterface.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInterface_GetPublishedMetaObject[];
extern char igLockInterface_GetVTable[];
extern char thunk_igLockInterface_GetMetaObject[];
extern char igInterface_Register[];
extern char g_igLockInterface_callbackList[];
extern char igLockInterface_className[];
extern char g_igLockInterface_metaObject[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();
int igLockInterface_InitFields();

void igLockInterface_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLockInterface_metaObject,       /* published MetaObject slot */
        igInterface_Register,                        /* base class registrar */
        igInterface_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igLockInterface_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igLockInterface_className,        /* class name */
        0x2C,                                        /* instance size */
        igLockInterface_GetVTable,                   /* vtable getter */
        &igLockInterface_InitFields,                 /* field adder */
        0,                                           /* extra callback item */
        g_igLockInterface_callbackList      /* callback list */
    );
}
