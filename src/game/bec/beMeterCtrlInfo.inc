igMetaObject *g_beMeterCtrlInfo_metaObject;
igMetaField *g_beMeterCtrlInfo_oneDataListMetaField;

void *beMeterCtrlInfo_GetMetaObject(void) {
    bool ok;
    if (g_beMeterCtrlInfo_metaObject == 0) goto make;
    ok = !!(g_beMeterCtrlInfo_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beMeterCtrlInfo_EnsureRegistered();
done:;
    return g_beMeterCtrlInfo_metaObject;
}

int beMeterCtrlInfo_GetVTable(void) {
    Obj_3570f0 o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[4] = 0;
    o.w[5] = 0;
    o.vt = &g_beMeterCtrlInfo_vtable[0];
    o.s = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beMeterCtrlInfo_vtable[0];
    FUN_00199450(&o.s, -1);
    FUN_0033ec80((struct S_33ec80 *)&o, (short)0);
    return r;
}

void beMeterCtrlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMeterCtrlInfo_Register);
}

static igMetaObjectCallback g_beMeterCtrlInfo_callbackList[] = { igNamedObjectList_EnsureRegistered, 0 };

void *beMeterCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMeterCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beMeterCtrlInfo_GetMetaObjectFunction,
        "beMeterCtrlInfo",
        0x20, /* instance size */
        beMeterCtrlInfo_GetVTable,
        beMeterCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beMeterCtrlInfo_callbackList /* callback list */
    );
}

void beMeterCtrlInfo_GetMetaObjectFunction(void)
{
    beMeterCtrlInfo_GetMetaObject();
}

static FieldFactory g_beMeterCtrlInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beMeterCtrlInfo_fieldTable[] = {
    "_oneDataList",
};
static igMetaField **g_beMeterCtrlInfo_fieldHandles[] = {
    &g_beMeterCtrlInfo_oneDataListMetaField,
};
static int g_beMeterCtrlInfo_fieldOffsets[] = {
    28,
};

void beMeterCtrlInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMeterCtrlInfo_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beMeterCtrlInfo_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beMeterCtrlInfo_fieldTable, g_beMeterCtrlInfo_fieldHandles, g_beMeterCtrlInfo_fieldOffsets, temp_s2);
}

