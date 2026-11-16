igMetaObject *g_beGeneraterInfo_metaObject;
igMetaField *g_beGeneraterInfo_dataListMetaField;

igMetaObject *beGeneraterInfo_GetMetaObject(void) {
    igMetaObject *g = g_beGeneraterInfo_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beGeneraterInfo_EnsureRegistered();
done:
    return g_beGeneraterInfo_metaObject;
}

int beGeneraterInfo_GetVTable(void) {
    struct F f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[1] = 0;
    f.w[4] = 0;
    f.w[5] = 0;
    f.vt = &g_beGeneraterInfo_vtable[0];
    f.w[6] = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
    f.vt = &g_beGeneraterInfo_vtable[0];
    FUN_0035f7f0((igSmartPointer<igObject> *)(&f.w[6]), (long long)(-1));
    FUN_0033ec80((struct S_33ec80 *)&f, (short)0);
    return temp_s0;
}

igSmartPointer<igObject> *FUN_0035f7f0(igSmartPointer<igObject> *self, long long delete_storage) {
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

void beGeneraterInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterInfo_Register);
}

static igMetaObjectCallback g_beGeneraterInfo_callbackList[] = { beGeneraterDataList_EnsureRegistered, 0 };

void *beGeneraterInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beGeneraterInfo_GetMetaObjectFunction,
        "beGeneraterInfo",
        0x20, /* instance size */
        beGeneraterInfo_GetVTable,
        beGeneraterInfo_InitFields,
        0, /* extra callback item */
        g_beGeneraterInfo_callbackList /* callback list */
    );
}

void beGeneraterInfo_GetMetaObjectFunction(void)
{
    beGeneraterInfo_GetMetaObject();
}

static FieldFactory g_beGeneraterInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beGeneraterInfo_fieldTable[] = {
    "_dataList",
};
static igMetaField **g_beGeneraterInfo_fieldHandles[] = {
    &g_beGeneraterInfo_dataListMetaField,
};
static int g_beGeneraterInfo_fieldOffsets[] = {
    28,
};

void beGeneraterInfo_InitFields(void) {
    int base;
    void *dataList;
    void *meta;

    meta = (void *)g_beGeneraterInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beGeneraterInfo_ctorTable, 1);
    dataList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)dataList)->_metaObject = (int)beGeneraterDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)dataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beGeneraterInfo_fieldTable, g_beGeneraterInfo_fieldHandles, g_beGeneraterInfo_fieldOffsets, base);
}

