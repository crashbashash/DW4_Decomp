igMetaObject *g_igLightStateAttr_metaObject;
igMetaField *g_igLightStateAttr_lightMetaField;
igMetaField *g_igLightStateAttr_enabledMetaField;
igMetaField *g_igLightStateAttr_internalMetaField;

igLightStateAttr *igLightStateAttr_Create(igMemoryPoolView *pool) {
    igLightStateAttr_EnsureRegistered();
    return (igLightStateAttr *)igMetaObject_CreateInstance(g_igLightStateAttr_metaObject, pool);
}

igMetaObject *igLightStateAttr_GetOrCreateMetaObject(void) {
    if (g_igLightStateAttr_metaObject == 0) {
        g_igLightStateAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igLightStateAttr_metaObject;
}

igMetaObject *igLightStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igLightStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igLightStateAttr_EnsureRegistered();
    return g_igLightStateAttr_metaObject;
}

int igLightStateAttr_GetVTable(void) {
    union U_136290 u;
    int t;
    char *o;
    int *a1;
    int v0;
    S_ref *p0, *p1;
    igObject_InitHeader((igObject *)u.b);
    p0 = (S_ref *)&u.b[12];
    p1 = (S_ref *)&u.b[16];
    u.vt = (int)&g_igLightStateAttr_vtable[0];
    *(int *)p0 = 0;
    *(int *)p1 = 0;
    t = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igLightStateAttr_vtable[0];
    if (p1 != 0) {
        p1 = *(S_ref **)p1;
        if (p1 != 0) {
            p1->f4 = (int)((int) (p1->f4 - 1));
            if (((unsigned long long) ((long long) p1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)p1);
            }
        }
    }
    if (p0 != 0) {
        p0 = *(S_ref **)p0;
        if (p0 != 0) {
            p0->f4 = (int)((int) (p0->f4 - 1));
            if (((unsigned long long) ((long long) p0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)p0);
            }
        }
    }
    return t;
}

ObjectRefWord *FUN_00136370(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((igObject *)object);
        }
        if((short)delete_storage>0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igObject_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

void igLightStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLightStateAttr_Register);
}

static igMetaObjectCallback g_igLightStateAttr_callbackList[] = { igLightAttr_EnsureRegistered, Gap::Core::igObject::arkRegister, 0 };

CallbackArray *igLightStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLightStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igLightStateAttr_GetMetaObjectFunction,
        "igLightStateAttr",
        0x18, /* instance size */
        igLightStateAttr_GetVTable,
        &igLightStateAttr_InitFields,
        0, /* extra callback item */
        g_igLightStateAttr_callbackList /* callback list */
    );
}

void igLightStateAttr_GetMetaObjectFunction(void) {
    igLightStateAttr_GetMetaObject();
}

static FieldFactory g_igLightStateAttr_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igLightStateAttr_fieldTable[] = {
    "_light",
    "_enabled",
    "_internal",
};
static igMetaField **g_igLightStateAttr_fieldHandles[] = {
    &g_igLightStateAttr_lightMetaField,
    &g_igLightStateAttr_enabledMetaField,
    &g_igLightStateAttr_internalMetaField,
};
static int g_igLightStateAttr_fieldOffsets[] = {
    16,
    20,
    12,
};

void igLightStateAttr_InitFields(void) {
    int base;
    void *field;
    void *field2;
    igMetaObject *meta;

    meta = g_igLightStateAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igLightStateAttr_ctorTable, 3);
    field2 = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)field2)->_metaObject = (int)igLightAttr_GetOrCreateMetaObject();
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt(meta, base + 1)))->setDefault(1);
    field = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)field)->_metaObject = (int)Gap::Core::igObject::getClassMeta();
    ((igMetaField *)field)->_persistent = 0;
    igMetaObject_NameFields(meta, g_igLightStateAttr_fieldTable, g_igLightStateAttr_fieldHandles, g_igLightStateAttr_fieldOffsets, base);
}

