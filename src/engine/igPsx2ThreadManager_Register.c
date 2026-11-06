/* 0x002cf370 igPsx2ThreadManager_Register: registers class igPsx2ThreadManager with the object system, derived from igThreadManager.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igThreadManager_Register[];
extern char thunk_igPsx2ThreadManager_GetMetaObject[];
extern char igPsx2ThreadManager_GetVTable[];
extern char igThreadManager_GetPublishedMetaObject[];
extern char igPsx2ThreadManager_className[];
extern char g_igPsx2ThreadManager_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igPsx2ThreadManager_InitFields_002cf3f0[4];
void igPsx2ThreadManager_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2ThreadManager_metaObject,       /* published MetaObject slot */
        igThreadManager_Register,                        /* base class registrar */
        igThreadManager_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPsx2ThreadManager_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igPsx2ThreadManager_className,        /* class name */
        0x10,                                            /* instance size */
        igPsx2ThreadManager_GetVTable,                   /* vtable getter */
        &igPsx2ThreadManager_InitFields_002cf3f0[0],     /* field adder (post_init in data/reflection.json) */
        0,                                               /* extra callback-vector item (none) */
        0                                                /* zero-terminated callback-vector item list (none) */
    );
}
