igMetaObject *g_igImageUtils_metaObject;

igMetaObject *igImageUtils_GetMetaObject(void)
{
    igMetaObject *g = g_igImageUtils_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igImageUtils_EnsureRegistered();
    return g_igImageUtils_metaObject;
}

void igImageUtils_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igImageUtils_Register);
}

CallbackArray *igImageUtils_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igImageUtils_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igImageUtils_GetMetaObjectFunction,
        "igImageUtils",
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igImageUtils_GetMetaObjectFunction(void) {
    igImageUtils_GetMetaObject();
}

igSmartPointer<igObject> *FUN_0014dd40(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

