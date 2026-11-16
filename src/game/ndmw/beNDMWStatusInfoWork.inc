igMetaObject *g_beNDMWStatusInfoWork_metaObject;
igMetaField *g_beNDMWStatusInfoWork_parameterMetaField;
igMetaField *g_beNDMWStatusInfoWork_previewMetaField;
igMetaField *g_beNDMWStatusInfoWork_weaponSalesListMetaField;
igMetaField *g_beNDMWStatusInfoWork_armorSalesListMetaField;
igMetaField *g_beNDMWStatusInfoWork_chipSalesListMetaField;
igMetaField *g_beNDMWStatusInfoWork_junkSalesListMetaField;
igMetaField *g_beNDMWStatusInfoWork_junkGiftMetaField;

void beNDMWStatusInfoWork_Create(int arg0) {
    beNDMWStatusInfoWork_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusInfoWork_metaObject, arg0);
}

igMetaObject *beNDMWStatusInfoWork_GetOrCreateMetaObject(void) {
    if (g_beNDMWStatusInfoWork_metaObject == 0) {
        g_beNDMWStatusInfoWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    struct Obj_3b5fa0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &g_beNDMWStatusInfoWork_vtable[0];
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.w[6] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWStatusInfoWork_vtable[0];
    igSmartPointer_beNDMWItemBaseList_Destruct((void **)(&obj.w[6]), (long long)(-1));
    igSmartPointer_beNDMWItemBaseList_Destruct((void **)(&obj.w[5]), (long long)(-1));
    igSmartPointer_beNDMWItemBaseList_Destruct((void **)(&obj.w[4]), (long long)(-1));
    igSmartPointer_beNDMWItemBaseList_Destruct((void **)(&obj.w[3]), (long long)(-1));
    igSmartPointer_igIntList_Destruct(&obj.w[2], -1);
    igSmartPointer_igIntList_Destruct(&obj.w[1], -1);
    return r;
}

void **igSmartPointer_beNDMWItemBaseList_Destruct(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void beNDMWStatusInfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusInfoWork_Register);
}

static igMetaObjectCallback g_beNDMWStatusInfoWork_callbackList[] = { igIntList_EnsureRegistered, beNDMWItemBaseList_EnsureRegistered, 0 };

void *beNDMWStatusInfoWork_Register(void) {
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
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s1;
    int temp_s0;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (void *)g_beNDMWStatusInfoWork_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWStatusInfoWork_ctorTable, 7);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWStatusInfoWork_fieldTable, g_beNDMWStatusInfoWork_fieldHandles, g_beNDMWStatusInfoWork_fieldOffsets, temp_s0);
}

