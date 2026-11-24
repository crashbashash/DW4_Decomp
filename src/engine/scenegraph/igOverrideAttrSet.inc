igMetaObject *g_igOverrideAttrSet_metaObject;

igMetaObject *igOverrideAttrSet_GetOrCreateMetaObject(void) {
    if (g_igOverrideAttrSet_metaObject == 0) {
        g_igOverrideAttrSet_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igOverrideAttrSet_metaObject;
}

igMetaObject *igOverrideAttrSet_GetMetaObject(void)
{
    igMetaObject *g = g_igOverrideAttrSet_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igOverrideAttrSet_EnsureRegistered();
    return g_igOverrideAttrSet_metaObject;
}

int igOverrideAttrSet_GetVTable(void) {
    struct F f;
    int temp_s0;

    igObject_InitHeader((igObject *)&f);
    f.w[1] = 0;
    f.w[2] = 0;
    f.w[3] = 0;
    f.w[6] = 0;
    f.w[7] = 0;
    f.vt = &g_igOverrideAttrSet_vtable[0];
    temp_s0 = *(int *)((char *)&f + g_objectSystem->vtableProbeOffset);
    f.vt = &g_igOverrideAttrSet_vtable[0];
    FUN_0019c0e0((struct S_19c0e0 *)&f, 0);
    return temp_s0;
}

void igOverrideAttrSet_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igOverrideAttrSet_Register);
}

CallbackArray *igOverrideAttrSet_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igOverrideAttrSet_metaObject,
        Gap::Sg::igAttrSet::arkRegisterInternal,
        Gap::Sg::igAttrSet::getClassMeta,
        igOverrideAttrSet_GetMetaObjectFunction,
        "igOverrideAttrSet",
        0x28, /* instance size */
        igOverrideAttrSet_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igOverrideAttrSet_GetMetaObjectFunction(void) {
    igOverrideAttrSet_GetMetaObject();
}

igSmartPointer<igObject> *igSmartPointer_igMetaObject_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

