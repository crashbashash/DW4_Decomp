/* Static-init registration of igVolume, an abstract class derived from igObject (abstract state 1,
 * so no vtable getter; instance size 8). FUN_00186a40 is the set-once latch (a gp byte flag guards
 * a few shared one-time registrations); FUN_00186bc0 is igVolume's own extra callback item
 * (RegisterClass's stack argument 2). */
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
        1, /* abstract */
        g_igVolume_metaObject,
        igObject_Register,                     /* base class registrar (igObject) */
        igObject_GetMetaObject_ParentAccessor,
        thunk_igVolume_GetMetaObject,
        igVolume_className,
        8, /* instance size */
        0,
        &igVolume_InitFields_00186bb0[0],      /* field adder (class InitFields) */
        FUN_00186bc0, /* extra callback item */
        0 /* callback list */
    );
}
