igMetaObject *g_igVisualContextAttrDefaultManager_metaObject;
igMetaField *g_igVisualContextAttrDefaultManager_visualContextMetaField;

igVisualContextAttrDefaultManager *igVisualContextAttrDefaultManager_Create(igMemoryPoolView *pool) {
    igVisualContextAttrDefaultManager_EnsureRegistered();
    return (igVisualContextAttrDefaultManager *)igMetaObject_CreateInstance(g_igVisualContextAttrDefaultManager_metaObject, pool);
}

igMetaObject *igVisualContextAttrDefaultManager_GetMetaObject(void)
{
    igMetaObject *g = g_igVisualContextAttrDefaultManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVisualContextAttrDefaultManager_EnsureRegistered();
    return g_igVisualContextAttrDefaultManager_metaObject;
}

int igVisualContextAttrDefaultManager_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *p;

    igObject_InitHeader((igObject *)u.b);
    p = (S_ref *)&u.b[8];
    u.vt = (int)&g_igVisualContextAttrDefaultManager_vtable[0];
    *(int *)p = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igVisualContextAttrDefaultManager_vtable[0];
    if (p != 0) {
        p = *(S_ref **)p;
        if (p != 0) {
            p->f4 = (int)((int) (p->f4 - 1));
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)p);
            }
        }
    }
    return temp_s0;
}

igSmartPointer<igObject> *igSmartPointer_igVisualContext_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

void igVisualContextAttrDefaultManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVisualContextAttrDefaultManager_Register);
}

static igMetaObjectCallback g_igVisualContextAttrDefaultManager_callbackList[] = { igVisualContext_EnsureRegistered, 0 };

CallbackArray *igVisualContextAttrDefaultManager_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVisualContextAttrDefaultManager_metaObject,
        igAttrDefaultManager_Register,
        igAttrDefaultManager_GetPublishedMetaObject,
        igVisualContextAttrDefaultManager_GetMetaObjectFunction,
        "igVisualContextAttrDefaultManager",
        0xC, /* instance size */
        igVisualContextAttrDefaultManager_GetVTable,
        &igVisualContextAttrDefaultManager_InitFields,
        0, /* extra callback item */
        g_igVisualContextAttrDefaultManager_callbackList /* callback list */
    );
}

void igVisualContextAttrDefaultManager_GetMetaObjectFunction(void) {
    igVisualContextAttrDefaultManager_GetMetaObject();
}

igMetaObject *igAttrDefaultManager_GetPublishedMetaObject(void) {
    return g_igAttrDefaultManager_metaObject;
}

static FieldFactory g_igVisualContextAttrDefaultManager_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igVisualContextAttrDefaultManager_fieldTable[] = {
    "_visualContext",
};
static igMetaField **g_igVisualContextAttrDefaultManager_fieldHandles[] = {
    &g_igVisualContextAttrDefaultManager_visualContextMetaField,
};
static int g_igVisualContextAttrDefaultManager_fieldOffsets[] = {
    8,
};

void igVisualContextAttrDefaultManager_InitFields(void) {
    int base;
    void *field;
    igMetaObject *meta;

    meta = g_igVisualContextAttrDefaultManager_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igVisualContextAttrDefaultManager_ctorTable, 1);
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igVisualContext_GetOrCreateMetaObject();
    ((igMetaField *)field)->_persistent = 0;
    ((igMetaField *)field)->_deepCopyMethod = 1;
    ((igMetaField *)field)->_shallowCopyMethod = 1;
    igMetaObject_NameFields(meta, g_igVisualContextAttrDefaultManager_fieldTable, g_igVisualContextAttrDefaultManager_fieldHandles, g_igVisualContextAttrDefaultManager_fieldOffsets, base);
}

