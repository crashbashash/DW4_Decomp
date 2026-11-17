igMetaObject *g_beNDMWStatusInfoWork_metaObject;
igMetaField *g_beNDMWStatusInfoWork_parameterMetaField;
igMetaField *g_beNDMWStatusInfoWork_previewMetaField;
igMetaField *g_beNDMWStatusInfoWork_weaponSalesListMetaField;
igMetaField *g_beNDMWStatusInfoWork_armorSalesListMetaField;
igMetaField *g_beNDMWStatusInfoWork_chipSalesListMetaField;
igMetaField *g_beNDMWStatusInfoWork_junkSalesListMetaField;
igMetaField *g_beNDMWStatusInfoWork_junkGiftMetaField;

beNDMWStatusInfoWork *beNDMWStatusInfoWork_Create(int allocator) {
    beNDMWStatusInfoWork_EnsureRegistered();
    return (beNDMWStatusInfoWork *)igMetaObject_CreateInstance(g_beNDMWStatusInfoWork_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWStatusInfoWork_GetOrCreateMetaObject(void) {
    if (g_beNDMWStatusInfoWork_metaObject == 0) {
        g_beNDMWStatusInfoWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWStatusInfoWork_metaObject;
}

void *beNDMWStatusInfoWork_GetMetaObject(void) {
    bool ok;
    if (g_beNDMWStatusInfoWork_metaObject == 0) goto make;
    ok = !!(g_beNDMWStatusInfoWork_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beNDMWStatusInfoWork_EnsureRegistered();
done:;
    return g_beNDMWStatusInfoWork_metaObject;
}

int beNDMWStatusInfoWork_GetVTable(void) {
    beNDMWStatusInfoWork obj;
    int vtable;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWStatusInfoWork_vtable[0];
    obj._parameter = 0;
    obj._preview = 0;
    obj._weaponSalesList = 0;
    obj._armorSalesList = 0;
    obj._chipSalesList = 0;
    obj._junkSalesList = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWStatusInfoWork_vtable[0];
    igSmartPointer_beNDMWItemBaseList_Destruct((igSmartPointer<igObject> *)&obj._junkSalesList, -1);
    igSmartPointer_beNDMWItemBaseList_Destruct((igSmartPointer<igObject> *)&obj._chipSalesList, -1);
    igSmartPointer_beNDMWItemBaseList_Destruct((igSmartPointer<igObject> *)&obj._armorSalesList, -1);
    igSmartPointer_beNDMWItemBaseList_Destruct((igSmartPointer<igObject> *)&obj._weaponSalesList, -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._preview, -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._parameter, -1);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWItemBaseList_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

void beNDMWStatusInfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusInfoWork_Register);
}

static igMetaObjectCallback g_beNDMWStatusInfoWork_callbackList[] = { igIntList_EnsureRegistered, beNDMWItemBaseList_EnsureRegistered, 0 };

CallbackArray *beNDMWStatusInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWStatusInfoWork_GetMetaObjectFunction,
        "beNDMWStatusInfoWork",
        0x24, /* instance size */
        beNDMWStatusInfoWork_GetVTable,
        beNDMWStatusInfoWork_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusInfoWork_callbackList /* callback list */
    );
}

void beNDMWStatusInfoWork_GetMetaObjectFunction(void)
{
    beNDMWStatusInfoWork_GetMetaObject();
}

static FieldFactory g_beNDMWStatusInfoWork_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWStatusInfoWork_fieldTable[] = {
    "_parameter",
    "_preview",
    "_weaponSalesList",
    "_armorSalesList",
    "_chipSalesList",
    "_junkSalesList",
    "_junkGift",
};
static igMetaField **g_beNDMWStatusInfoWork_fieldHandles[] = {
    &g_beNDMWStatusInfoWork_parameterMetaField,
    &g_beNDMWStatusInfoWork_previewMetaField,
    &g_beNDMWStatusInfoWork_weaponSalesListMetaField,
    &g_beNDMWStatusInfoWork_armorSalesListMetaField,
    &g_beNDMWStatusInfoWork_chipSalesListMetaField,
    &g_beNDMWStatusInfoWork_junkSalesListMetaField,
    &g_beNDMWStatusInfoWork_junkGiftMetaField,
};
static int g_beNDMWStatusInfoWork_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
};

void beNDMWStatusInfoWork_InitFields(void) {
    void *parameter;
    void *preview;
    void *weaponSalesList;
    void *armorSalesList;
    void *chipSalesList;
    void *junkSalesList;
    void *meta;
    int base;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)g_beNDMWStatusInfoWork_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWStatusInfoWork_ctorTable, 7);
    parameter = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base));
    ((igObjectRefMetaField *)parameter)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)parameter)->_construct = 1;
    preview = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1));
    ((igObjectRefMetaField *)preview)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)preview)->_construct = 1;
    weaponSalesList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2));
    ((igObjectRefMetaField *)weaponSalesList)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    ((igRefMetaField *)weaponSalesList)->_construct = 1;
    armorSalesList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3));
    ((igObjectRefMetaField *)armorSalesList)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    ((igRefMetaField *)armorSalesList)->_construct = 1;
    chipSalesList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4));
    ((igObjectRefMetaField *)chipSalesList)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    ((igRefMetaField *)chipSalesList)->_construct = 1;
    junkSalesList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5));
    ((igObjectRefMetaField *)junkSalesList)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    ((igRefMetaField *)junkSalesList)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWStatusInfoWork_fieldTable, g_beNDMWStatusInfoWork_fieldHandles, g_beNDMWStatusInfoWork_fieldOffsets, base);
}

