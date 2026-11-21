igMetaObject *g_igSetRenderDestinationAttr_metaObject;
igMetaField *g_igSetRenderDestinationAttr_pRDAttrMetaField;

igMetaObject *igSetRenderDestinationAttr_GetOrCreateMetaObject(void) {
    if (g_igSetRenderDestinationAttr_metaObject == 0) {
        g_igSetRenderDestinationAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igSetRenderDestinationAttr_metaObject;
}

igMetaObject *igSetRenderDestinationAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igSetRenderDestinationAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igSetRenderDestinationAttr_EnsureRegistered();
    return g_igSetRenderDestinationAttr_metaObject;
}

int igSetRenderDestinationAttr_GetVTable(void) {
    union U_133c10 u;
    void **q3;
    int temp_s0;
    void *temp_a0;

    igObject_InitHeader((igObject *)u.b);
    q3 = &u.p[3];
    u.w[0] = (int)(&g_igSetRenderDestinationAttr_vtable[0]);
    *q3 = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.w[0] = (int)(&g_igSetRenderDestinationAttr_vtable[0]);
    if (q3 != 0) {
        temp_a0 = *q3;
        if (temp_a0 != 0) {
            *(int *)((char *)(temp_a0) + 4) = (int)((int) (*(int *)((char *)(temp_a0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_a0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
    }
    return temp_s0;
}

ObjectRefWord *FUN_00133ca0(ObjectRefWord *self,int delete_storage) {
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

void igSetRenderDestinationAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igSetRenderDestinationAttr_Register);
}

static igMetaObjectCallback g_igSetRenderDestinationAttr_callbackList[] = { igRenderDestinationAttr_EnsureRegistered, 0 };

CallbackArray *igSetRenderDestinationAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igSetRenderDestinationAttr_metaObject,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        igSetRenderDestinationAttr_GetMetaObjectFunction,
        "igSetRenderDestinationAttr",
        0x10, /* instance size */
        igSetRenderDestinationAttr_GetVTable,
        &igSetRenderDestinationAttr_InitFields,
        0, /* extra callback item */
        g_igSetRenderDestinationAttr_callbackList /* callback list */
    );
}

void igSetRenderDestinationAttr_GetMetaObjectFunction(void) {
    igSetRenderDestinationAttr_GetMetaObject();
}

static FieldFactory g_igSetRenderDestinationAttr_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igSetRenderDestinationAttr_fieldTable[] = {
    "_pRDAttr",
};
static igMetaField **g_igSetRenderDestinationAttr_fieldHandles[] = {
    &g_igSetRenderDestinationAttr_pRDAttrMetaField,
};
static int g_igSetRenderDestinationAttr_fieldOffsets[] = {
    12,
};

void igSetRenderDestinationAttr_InitFields(void) {
    int base;
    void *field;
    igMetaObject *meta;

    meta = g_igSetRenderDestinationAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igSetRenderDestinationAttr_ctorTable, 1);
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igRenderDestinationAttr_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_igSetRenderDestinationAttr_fieldTable, g_igSetRenderDestinationAttr_fieldHandles, g_igSetRenderDestinationAttr_fieldOffsets, base);
}

