igMetaObject *g_igTextureBindAttr_metaObject;
igMetaField *g_igTextureBindAttr_textureMetaField;
igMetaField *g_igTextureBindAttr_unitIDMetaField;

igTextureBindAttr *igTextureBindAttr_CreateInstance(int allocator) {
    igTextureBindAttr_EnsureRegistered();
    return (igTextureBindAttr *)igMetaObject_CreateInstance(g_igTextureBindAttr_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igTextureBindAttr_GetOrCreateMetaObject(void) {
    if (g_igTextureBindAttr_metaObject == 0) {
        g_igTextureBindAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTextureBindAttr_metaObject;
}

igMetaObject *igTextureBindAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureBindAttr_metaObject != 0) {
        ready = (g_igTextureBindAttr_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igTextureBindAttr_EnsureRegistered();
done:
    return g_igTextureBindAttr_metaObject;
}

int igTextureBindAttr_GetVTable(void) {
    struct Obj_1328f0 obj;
    char *o;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igTextureBindAttr_vtable[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igTextureBindAttr_vtable[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
    }
    return t;
}

igSmartPointer<igObject> *igSmartPointer_igTextureAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

void igTextureBindAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextureBindAttr_Register);
}

static igMetaObjectCallback g_igTextureBindAttr_callbackList[] = { igTextureAttr_EnsureRegistered, 0 };

CallbackArray *igTextureBindAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureBindAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igTextureBindAttr_GetMetaObjectFunction,
        "igTextureBindAttr",
        0x14, /* instance size */
        igTextureBindAttr_GetVTable,
        &igTextureBindAttr_InitFields,
        thunk_igTextureBindAttr_ConfigureFastApply, /* extra callback item */
        g_igTextureBindAttr_callbackList /* callback list */
    );
}

void igTextureBindAttr_GetMetaObjectFunction(void) {
    igTextureBindAttr_GetMetaObject();
}

static FieldFactory g_igTextureBindAttr_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igTextureBindAttr_fieldTable[] = {
    "_texture",
    "_unitID",
};
static igMetaField **g_igTextureBindAttr_fieldHandles[] = {
    &g_igTextureBindAttr_textureMetaField,
    &g_igTextureBindAttr_unitIDMetaField,
};
static int g_igTextureBindAttr_fieldOffsets[] = {
    12,
    16,
};

void igTextureBindAttr_InitFields(void) {
    int base;
    void *field;
    igMetaObject *meta;
    meta = g_igTextureBindAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igTextureBindAttr_ctorTable, 2);
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igTextureAttr_GetOrCreateMetaObject();
    field = igMetaObject_GetFieldAt(meta, base + 1);
    ((igMetaField *)field)->_invarianceFunction = (int)igTextureBindAttr_SynchronizeCachedUnitID;
    igMetaObject_NameFields(meta, g_igTextureBindAttr_fieldTable, g_igTextureBindAttr_fieldHandles, g_igTextureBindAttr_fieldOffsets, base);
}

void thunk_igTextureBindAttr_ConfigureFastApply(void) {
    igTextureBindAttr_ConfigureFastApply();
}

