igMetaObject *g_beNDMWShopCtrlA0_metaObject;
igMetaField *g_beNDMWShopCtrlA0_accountMetaField;
igMetaField *g_beNDMWShopCtrlA0_playerNoListMetaField;

beNDMWShopCtrlA0 *beNDMWShopCtrlA0_Create(int allocator) {
    beNDMWShopCtrlA0_EnsureRegistered();
    return (beNDMWShopCtrlA0 *)igMetaObject_CreateInstance(g_beNDMWShopCtrlA0_metaObject, allocator);
}

void *beNDMWShopCtrlA0_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopCtrlA0_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopCtrlA0_EnsureRegistered();
    }
    return g_beNDMWShopCtrlA0_metaObject;
}

int beNDMWShopCtrlA0_GetVTable(void) {
    beNDMWShopCtrlA0 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopCtrlA0_vtable[0];
    obj._account = 0;
    obj._playerNoList = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopCtrlA0_vtable[0];
    igSmartPointer_igIntList_Destruct(&obj._playerNoList, -1);
    igSmartPointer_beNDMWStatusTitle03_Destruct((igSmartPointer<igObject> *)&obj._account, -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWStatusTitle03_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
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

void beNDMWShopCtrlA0_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlA0_Register);
}

static igMetaObjectCallback g_beNDMWShopCtrlA0_callbackList[] = { beNDMWStatusTitle03_EnsureRegistered, igIntList_EnsureRegistered, 0 };

void *beNDMWShopCtrlA0_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrlA0_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlA0_GetMetaObjectFunction,
        "beNDMWShopCtrlA0",
        0x5c, /* instance size */
        beNDMWShopCtrlA0_GetVTable,
        beNDMWShopCtrlA0_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlA0_callbackList /* callback list */
    );
}

void beNDMWShopCtrlA0_GetMetaObjectFunction(void)
{
    beNDMWShopCtrlA0_GetMetaObject();
}

static FieldFactory g_beNDMWShopCtrlA0_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWShopCtrlA0_fieldTable[] = {
    "_account",
    "_playerNoList",
};
static igMetaField **g_beNDMWShopCtrlA0_fieldHandles[] = {
    &g_beNDMWShopCtrlA0_accountMetaField,
    &g_beNDMWShopCtrlA0_playerNoListMetaField,
};
static int g_beNDMWShopCtrlA0_fieldOffsets[] = {
    84,
    88,
};

void beNDMWShopCtrlA0_InitFields(void) {
    int base;
    void *account;
    void *playerNoList;
    igMetaObject *meta;

    meta = g_beNDMWShopCtrlA0_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWShopCtrlA0_ctorTable, 2);
    account = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)account)->_metaObject = (int)beNDMWStatusTitle03_GetOrCreateMetaObject();
    playerNoList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)playerNoList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)playerNoList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWShopCtrlA0_fieldTable, g_beNDMWShopCtrlA0_fieldHandles, g_beNDMWShopCtrlA0_fieldOffsets, base);
}

