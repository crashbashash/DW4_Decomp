void FUN_00186a40(void) {
    if (DAT_00554b7c == 0) {
        DAT_00554b7c = 1;
        FUN_00186e40();
        FUN_00186f70();
        FUN_00190370();
    }
}

int FUN_00186a80(void) {
    if (DAT_00560f08[0] == 0) {
        DAT_00560f08[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00560f08[0];
}

igMetaObject *igVolume_GetMetaObject(void)
{
    igMetaObject *g = g_igVolume_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00186b20();
    return g_igVolume_metaObject[0];
}

void FUN_00186b20(void)
{
    igMetaObject_RunStaticInit(igVolume_Register);
}

/* Static-init registration of igVolume, an abstract class derived from igObject (abstract state 1,
 * so no vtable getter; instance size 8). FUN_00186a40 is the set-once latch (a gp byte flag guards
 * a few shared one-time registrations); FUN_00186bc0 is igVolume's own extra callback item
 * (RegisterClass's stack argument 2). */
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

void thunk_igVolume_GetMetaObject(void) {
    igVolume_GetMetaObject();
}

void FUN_00186bb0(void) {
    FUN_002fe480(&thunk_FUN_0018f4a0);
}

void FUN_00186bc0(void) {
    FUN_0018ec40();
    FUN_002fe490(&FUN_0018edb0);
}

void thunk_FUN_0018f4a0(void) {
    FUN_0018f4a0();
}

