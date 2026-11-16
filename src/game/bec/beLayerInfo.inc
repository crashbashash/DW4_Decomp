igMetaObject *g_beLayerInfo_metaObject;
igMetaField *g_beLayerInfo_groupsMetaField;

void *beLayerInfo_GetMetaObject(void) {
    igMetaObject *g = g_beLayerInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beLayerInfo_EnsureRegistered();
    }
    return g_beLayerInfo_metaObject;
}

int beLayerInfo_GetVTable(void) {
    union U_35c470 u;
    int t;
    char *ps;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&g_beLayerInfo_vtable[0];
    ps = &u.b[28];
    *(int *)ps = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beLayerInfo_vtable[0];
    FUN_0035c4f0((igSmartPointer<igObject> *)ps, -1);
    FUN_0033ec80((struct S_33ec80 *)u.b, (short)0);
    return t;
}

igSmartPointer<igObject> *FUN_0035c4f0(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

void beLayerInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLayerInfo_Register);
}

static igMetaObjectCallback g_beLayerInfo_callbackList[] = { beLayerGroupList_EnsureRegistered, 0 };

void *beLayerInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLayerInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beLayerInfo_GetMetaObjectFunction,
        "beLayerInfo",
        0x20, /* instance size */
        beLayerInfo_GetVTable,
        beLayerInfo_InitFields,
        0, /* extra callback item */
        g_beLayerInfo_callbackList /* callback list */
    );
}

void beLayerInfo_GetMetaObjectFunction(void)
{
    beLayerInfo_GetMetaObject();
}

static FieldFactory g_beLayerInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beLayerInfo_fieldTable[] = {
    "_groups",
};
static igMetaField **g_beLayerInfo_fieldHandles[] = {
    &g_beLayerInfo_groupsMetaField,
};
static int g_beLayerInfo_fieldOffsets[] = {
    28,
};

void beLayerInfo_InitFields(void) {
    int base;
    void *groups;
    void *meta;

    meta = (void *)g_beLayerInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beLayerInfo_ctorTable, 1);
    groups = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)groups)->_metaObject = (int)beLayerGroupList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beLayerInfo_fieldTable, g_beLayerInfo_fieldHandles, g_beLayerInfo_fieldOffsets, base);
}

