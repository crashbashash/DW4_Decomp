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
        thunk_igBase_GetMetaObject,
        "igBase",
        0x20, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igBase_GetMetaObject(void) {
    igBase_GetMetaObject();
}

igSmartPointer<igObject> *igSmartPointer_igGroup_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

void **FUN_002293d0(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

