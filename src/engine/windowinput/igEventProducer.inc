igMetaObject *igEventProducer_GetMetaObject(void)
{
    igMetaObject *g = g_igEventProducer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00146270();
    return g_igEventProducer_metaObject[0];
}

void FUN_00146270(void)
{
    igMetaObject_RunStaticInit(igEventProducer_Register);
}

void igEventProducer_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igEventProducer_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igEventProducer_GetMetaObject,
        igEventProducer_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igEventProducer_GetMetaObject(void) {
    igEventProducer_GetMetaObject();
}

int FUN_001462f0(void) {
    return g_igNonRefCountedObjectStack_metaObject[0];
}

