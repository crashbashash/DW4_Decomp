igMetaObject *g_igVolume_metaObject;

void FUN_00186a40(void) {
    if (g_MathsLibrary_registered == 0) {
        g_MathsLibrary_registered = 1;
        igVectorMorphing_EnsureRegistered();
        igVectorBlending_EnsureRegistered();
        FUN_00190370();
    }
}

igMetaObject *igVolume_GetOrCreateMetaObject(void) {
    if (g_igVolume_metaObject == 0) {
        g_igVolume_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igVolume_metaObject;
}

igMetaObject *igVolume_GetMetaObject(void)
{
    igMetaObject *g = g_igVolume_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVolume_EnsureRegistered();
    return g_igVolume_metaObject;
}

void igVolume_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVolume_Register);
}

/* Static-init registration of igVolume, an abstract class derived from igObject (abstract state 1,
 * so no vtable getter; instance size 8). FUN_00186a40 is the set-once latch (a gp byte flag guards
 * a few shared one-time registrations); FUN_00186bc0 is igVolume's own extra callback item
 * (RegisterClass's stack argument 2). */
CallbackArray *igVolume_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igVolume_metaObject,
        igObject_Register,                     /* base class registrar (igObject) */
        igObject_GetMetaObject_ParentAccessor,
        igVolume_GetMetaObjectFunction,
        "igVolume",
        8, /* instance size */
        0,
        (igMetaObjectCallback)&igVolume_InitFields_00186bb0[0],      /* field adder (class InitFields) */
        FUN_00186bc0, /* extra callback item */
        0 /* callback list */
    );
}

void igVolume_GetMetaObjectFunction(void) {
    igVolume_GetMetaObject();
}

void FUN_00186bb0(void) {
    igMetaObject_AddExitCallback((int)&thunk_FUN_0018f4a0);
}

void FUN_00186bc0(void) {
    FUN_0018ec40();
    igMetaObject_AddRegistrationCallback((int)&FUN_0018edb0);
}

void thunk_FUN_0018f4a0(void) {
    FUN_0018f4a0();
}

