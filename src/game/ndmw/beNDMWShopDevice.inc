igMetaObject *g_beNDMWShopDevice_metaObject;
igMetaField *g_beNDMWShopDevice_salesListMetaField;

beNDMWShopDevice *beNDMWShopDevice_Create(int allocator) {
    beNDMWShopDevice_EnsureRegistered();
    return (beNDMWShopDevice *)igMetaObject_CreateInstance(g_beNDMWShopDevice_metaObject, allocator);
}

void *beNDMWShopDevice_GetMetaObject(void) {
    unsigned char b;
    if (g_beNDMWShopDevice_metaObject != 0) {
        b = (g_beNDMWShopDevice_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beNDMWShopDevice_EnsureRegistered();
done:
    return g_beNDMWShopDevice_metaObject;
}

int beNDMWShopDevice_GetVTable(void) {
    beNDMWShopDevice obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopDevice_vtable[0];
    obj._salesList = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopDevice_vtable[0];
    igSmartPointer_beNDMWItemBaseList_Destruct((igSmartPointer<igObject> *)&obj._salesList, -1);
    beNDMWListCtrl_Destroy((beNDMWListCtrl *)&obj, 0);
    return vtable;
}

beNDMWListCtrl *beNDMWListCtrl_Destroy(beNDMWListCtrl *self, short flags) {
    if (self != 0) {
        *(int **)&self->_vtable = &g_beNDMWListCtrl_vtable[0];
        if (self != 0) {
            *(int **)&self->_vtable = &g_beNDMWWindowCtrl_vtable[0];
            beNDMWWindow_Destroy((beNDMWWindowCtrl *)self, 0);
        }
        if (flags > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

void beNDMWShopDevice_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopDevice_Register);
}

static igMetaObjectCallback g_beNDMWShopDevice_callbackList[] = { beNDMWItemBaseList_EnsureRegistered, 0 };

void *beNDMWShopDevice_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopDevice_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWShopDevice_GetMetaObjectFunction,
        "beNDMWShopDevice",
        0x64, /* instance size */
        beNDMWShopDevice_GetVTable,
        beNDMWShopDevice_InitFields,
        0, /* extra callback item */
        g_beNDMWShopDevice_callbackList /* callback list */
    );
}

void beNDMWShopDevice_GetMetaObjectFunction(void)
{
    beNDMWShopDevice_GetMetaObject();
}

igMetaObject *beNDMWListCtrl_GetPublishedMetaObject(void) {
    return g_beNDMWListCtrl_metaObject;
}

static FieldFactory g_beNDMWShopDevice_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWShopDevice_fieldTable[] = {
    "_salesList",
};
static igMetaField **g_beNDMWShopDevice_fieldHandles[] = {
    &g_beNDMWShopDevice_salesListMetaField,
};
static int g_beNDMWShopDevice_fieldOffsets[] = {
    96,
};

void beNDMWShopDevice_InitFields(void) {
    int base;
    void *salesList;
    igMetaObject *meta;

    meta = g_beNDMWShopDevice_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWShopDevice_ctorTable, 1);
    salesList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)salesList)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beNDMWShopDevice_fieldTable, g_beNDMWShopDevice_fieldHandles, g_beNDMWShopDevice_fieldOffsets, base);
}

