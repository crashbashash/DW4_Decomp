igMetaObject *g_beNDMWShopDevice_metaObject;
igMetaField *g_beNDMWShopDevice_salesListMetaField;

void beNDMWShopDevice_Create(int arg0) {
    beNDMWShopDevice_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopDevice_metaObject, arg0);
}

void *beNDMWShopDevice_GetMetaObject(void) {
    unsigned char b;
    if (g_beNDMWShopDevice_metaObject != 0) {
        b = (*(int *)((char *)(g_beNDMWShopDevice_metaObject) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    beNDMWShopDevice_EnsureRegistered();
done:
    return g_beNDMWShopDevice_metaObject;
}

int beNDMWShopDevice_GetVTable(void) {
    struct Obj_3b66e0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.vt = &g_beNDMWShopDevice_vtable[0];
    obj.w24 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWShopDevice_vtable[0];
    igSmartPointer_beNDMWItemBaseList_Destruct((void **)&obj.w24, (long long)(-1));
    FUN_003b6770((int **)&obj, (long long)0);
    return t;
}

int **FUN_003b6770(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &g_beNDMWListCtrl_vtable[0];
        if (arg0 != 0) {
            *arg0 = &g_beNDMWWindowCtrl_vtable[0];
            FUN_003b2d10((beNDMWWindowCtrl *)arg0, (short)0);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
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
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWShopDevice_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWShopDevice_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beNDMWShopDevice_fieldTable, g_beNDMWShopDevice_fieldHandles, g_beNDMWShopDevice_fieldOffsets, temp_s2);
}

