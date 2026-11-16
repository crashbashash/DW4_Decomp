igMetaObject *g_beNDMWShopCtrlEvolve_metaObject;
igMetaField *g_beNDMWShopCtrlEvolve_shinkaCtrlMetaField;

void beNDMWShopCtrlEvolve_Create(int allocator) {
    beNDMWShopCtrlEvolve_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopCtrlEvolve_metaObject, allocator);
}

void *beNDMWShopCtrlEvolve_GetMetaObject(void) {
    unsigned char b;
    if (g_beNDMWShopCtrlEvolve_metaObject != 0) {
        b = (*(int *)((char *)(g_beNDMWShopCtrlEvolve_metaObject) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    beNDMWShopCtrlEvolve_EnsureRegistered();
done:
    return g_beNDMWShopCtrlEvolve_metaObject;
}

int beNDMWShopCtrlEvolve_GetVTable(void) {
    union U_3b88f0 u;
    int temp_s0;
    int *p;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    u.vt = (int)&g_beNDMWShopCtrlEvolve_vtable[0];
    p = (int *)&u.b[96];
    *p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beNDMWShopCtrlEvolve_vtable[0];
    FUN_003b8980((igSmartPointer<igObject> *)p, -1);
    FUN_003b6770((int **)u.b, (long long)0);
    return temp_s0;
}

igSmartPointer<igObject> *FUN_003b8980(igSmartPointer<igObject> *self,int delete_storage) {
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

