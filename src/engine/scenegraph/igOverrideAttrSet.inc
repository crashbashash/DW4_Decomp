igMetaObject *g_igOverrideAttrSet_metaObject;

igMetaObject *FUN_0019c6a0(void) {
    if (g_igOverrideAttrSet_metaObject == 0) {
        g_igOverrideAttrSet_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igOverrideAttrSet_metaObject;
}

igMetaObject *igOverrideAttrSet_GetMetaObject(void)
{
    igMetaObject *g = g_igOverrideAttrSet_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019c7b0();
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
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)g_objectSystem + 916));
    f.vt = &g_igOverrideAttrSet_vtable[0];
    FUN_0019c0e0((struct S_19c0e0 *)&f, 0);
    return temp_s0;
}

void FUN_0019c7b0(void)
{
    igMetaObject_RunStaticInit(igOverrideAttrSet_Register);
}

CallbackArray *igOverrideAttrSet_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igOverrideAttrSet_metaObject,
        igAttrSet_Register,
        igAttrSet_GetPublishedMetaObject,
        thunk_igOverrideAttrSet_GetMetaObject,
        "igOverrideAttrSet",
        0x28, /* instance size */
        igOverrideAttrSet_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igOverrideAttrSet_GetMetaObject(void) {
    igOverrideAttrSet_GetMetaObject();
}

igSmartPointer<igObject> *igSmartPointer_igMetaObject_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

