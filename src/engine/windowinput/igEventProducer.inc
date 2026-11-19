igMetaObject *g_igEventProducer_metaObject;

igMetaObject *igEventProducer_GetMetaObject(void)
{
    igMetaObject *g = g_igEventProducer_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igEventProducer_EnsureRegistered();
    return g_igEventProducer_metaObject;
}

void igEventProducer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEventProducer_Register);
}

CallbackArray *igEventProducer_Register(void) {
    WindowInputLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igEventProducer_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igEventProducer_GetMetaObjectFunction,
        "igEventProducer",
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igEventProducer_GetMetaObjectFunction(void) {
    igEventProducer_GetMetaObject();
}

igMetaObject *igNonRefCountedObjectStack_GetPublishedMetaObject(void) {
    return g_igNonRefCountedObjectStack_metaObject;
}

