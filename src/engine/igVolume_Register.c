/* igVolume_Register: static-init registration of igVolume, an abstract class derived from igObject
 * (abstract state 1, so no vtable getter; instance size 8). The igMetaObject_RegisterClass
 * arguments are laid out per docs/engine/reflection-metadata.md section 1; names from
 * data/reflection.json. FUN_00186a40 is the set-once latch (a gp byte flag guards a few shared
 * one-time registrations); FUN_00186bc0 is igVolume's own extra callback item (passed as
 * RegisterClass's stack argument 2). */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igVolume_GetMetaObject[];
extern char FUN_00186bc0[];
extern char igObject_Register[];
extern char igVolume_className[];
extern char g_igVolume_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
extern int igVolume_InitFields_00186bb0[4];
void igVolume_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVolume_metaObject,        /* published MetaObject slot */
        igObject_Register,                     /* base class registrar (igObject) */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igVolume_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igVolume_className,         /* class name */
        8,                                     /* instance size */
        0,                                     /* vtable getter */
        &igVolume_InitFields_00186bb0[0],      /* field adder (class InitFields) */
        FUN_00186bc0,                          /* extra callback item */
        0                                      /* callback list */
    );
}
