igMetaObject *g_beNDMWLoadCtrl2Info_metaObject;
igMetaField *g_beNDMWLoadCtrl2Info_nameSelListMetaField;

igMetaObject *beNDMWLoadCtrl2Info_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWLoadCtrl2Info_metaObject != 0) {
        ready = (g_beNDMWLoadCtrl2Info_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    beNDMWLoadCtrl2Info_EnsureRegistered();
done:
    return g_beNDMWLoadCtrl2Info_metaObject;
}

int beNDMWLoadCtrl2Info_GetVTable(void) {
    union U_3c4a10 u;
    int temp_s0;
    int *p;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&g_beNDMWLoadCtrl2Info_vtable[0];
    p = (int *)&u.b[28];
    *p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beNDMWLoadCtrl2Info_vtable[0];
    igSmartPointer_igObjectList_Destruct(p, -1);
    FUN_0033ec80(u.b, 0);
    return temp_s0;
}

void beNDMWLoadCtrl2Info_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadCtrl2Info_Register);
}

static igMetaObjectCallback g_beNDMWLoadCtrl2Info_callbackList[] = { igObjectList_EnsureRegistered, 0 };

void *beNDMWLoadCtrl2Info_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadCtrl2Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWLoadCtrl2Info_GetMetaObject,
        "beNDMWLoadCtrl2Info",
        0x20, /* instance size */
        beNDMWLoadCtrl2Info_GetVTable,
        beNDMWLoadCtrl2Info_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadCtrl2Info_callbackList /* callback list */
    );
}

void beNDMWLoadCtrl2Info_GetMetaObject(void)
{
    beNDMWLoadCtrl2Info_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadCtrl2Info_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWLoadCtrl2Info_fieldTable[] = {
    "_nameSelList",
};
static igMetaField **g_beNDMWLoadCtrl2Info_fieldHandles[] = {
    &g_beNDMWLoadCtrl2Info_nameSelListMetaField,
};
static int g_beNDMWLoadCtrl2Info_fieldOffsets[] = {
    28,
};

void beNDMWLoadCtrl2Info_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWLoadCtrl2Info_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWLoadCtrl2Info_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igObjectList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beNDMWLoadCtrl2Info_fieldTable, g_beNDMWLoadCtrl2Info_fieldHandles, g_beNDMWLoadCtrl2Info_fieldOffsets, temp_s2);
}

