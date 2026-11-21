igMetaObject *g_igBase_metaObject;

igMetaObject *igBase_GetMetaObject(void)
{
    igMetaObject *g = g_igBase_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002292d0();
    return g_igBase_metaObject;
}

void FUN_002292d0(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igBase_Register);
}

CallbackArray *igBase_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igBase_metaObject,
        (igMetaObjectRegisterFunction)igInterfaced_Register,
        (igMetaObjectGetFunction)igInterfaced_GetPublishedMetaObject,
        igBase_GetMetaObjectFunction,
        "igBase",
        0x20, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igBase_GetMetaObjectFunction(void) {
    igBase_GetMetaObject();
}

igSmartPointer<igObject> *igSmartPointer_igGroup_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igIterateGraph_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

