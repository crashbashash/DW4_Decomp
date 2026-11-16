igMetaObject *g_beNDMWShopCtrlEvolve_metaObject;
igMetaField *g_beNDMWShopCtrlEvolve_shinkaCtrlMetaField;

beNDMWShopCtrlEvolve *beNDMWShopCtrlEvolve_Create(int allocator) {
    beNDMWShopCtrlEvolve_EnsureRegistered();
    return (beNDMWShopCtrlEvolve *)igMetaObject_CreateInstance(g_beNDMWShopCtrlEvolve_metaObject, allocator);
}

void *beNDMWShopCtrlEvolve_GetMetaObject(void) {
    unsigned char b;
    if (g_beNDMWShopCtrlEvolve_metaObject != 0) {
        b = (g_beNDMWShopCtrlEvolve_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beNDMWShopCtrlEvolve_EnsureRegistered();
done:
    return g_beNDMWShopCtrlEvolve_metaObject;
}

int beNDMWShopCtrlEvolve_GetVTable(void) {
    beNDMWShopCtrlEvolve obj;
    int vtable;
    int *shinkaCtrlRef;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopCtrlEvolve_vtable[0];
    shinkaCtrlRef = &obj._shinkaCtrl;
    *shinkaCtrlRef = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopCtrlEvolve_vtable[0];
    igSmartPointer_beNDMWShinkaCtrl_Destruct((igSmartPointer<igObject> *)shinkaCtrlRef, -1);
    beNDMWListCtrl_Destroy((beNDMWListCtrl *)&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWShinkaCtrl_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
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

void beNDMWShopCtrlEvolve_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlEvolve_Register);
}

static igMetaObjectCallback g_beNDMWShopCtrlEvolve_callbackList[] = { beNDMWShinkaCtrl_EnsureRegistered, 0 };

void *beNDMWShopCtrlEvolve_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrlEvolve_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlEvolve_GetMetaObjectFunction,
        "beNDMWShopCtrlEvolve",
        0x64, /* instance size */
        beNDMWShopCtrlEvolve_GetVTable,
        beNDMWShopCtrlEvolve_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlEvolve_callbackList /* callback list */
    );
}

void beNDMWShopCtrlEvolve_GetMetaObjectFunction(void)
{
    beNDMWShopCtrlEvolve_GetMetaObject();
}

static FieldFactory g_beNDMWShopCtrlEvolve_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWShopCtrlEvolve_fieldTable[] = {
    "_shinkaCtrl",
};
static igMetaField **g_beNDMWShopCtrlEvolve_fieldHandles[] = {
    &g_beNDMWShopCtrlEvolve_shinkaCtrlMetaField,
};
static int g_beNDMWShopCtrlEvolve_fieldOffsets[] = {
    96,
};

void beNDMWShopCtrlEvolve_InitFields(void) {
    int base;
    void *shinkaCtrl;
    igMetaObject *meta;

    meta = g_beNDMWShopCtrlEvolve_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWShopCtrlEvolve_ctorTable, 1);
    shinkaCtrl = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)shinkaCtrl)->_metaObject = (int)beNDMWShinkaCtrl_GetOrCreateMetaObject();
    ((igRefMetaField *)shinkaCtrl)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWShopCtrlEvolve_fieldTable, g_beNDMWShopCtrlEvolve_fieldHandles, g_beNDMWShopCtrlEvolve_fieldOffsets, base);
}

