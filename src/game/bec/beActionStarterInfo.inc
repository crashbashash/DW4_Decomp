igMetaObject *g_beActionStarterInfo_metaObject;
igMetaField *g_beActionStarterInfo_modelListMetaField;

void *beActionStarterInfo_GetMetaObject(void) {
    igMetaObject *g = g_beActionStarterInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beActionStarterInfo_EnsureRegistered();
    }
    return g_beActionStarterInfo_metaObject;
}

int beActionStarterInfo_GetVTable(void) {
    struct Obj_36b3b0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f14 = 0;
    obj.f18 = 0;
    obj.vt = &g_beActionStarterInfo_vtable[0];
    obj.f1c = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beActionStarterInfo_vtable[0];
    FUN_0036b430((O *)&obj.f1c, (short)(-1));
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return t;
}

O *FUN_0036b430(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

void beActionStarterInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beActionStarterInfo_Register);
}

static igMetaObjectCallback g_beActionStarterInfo_callbackList[] = { beAsTargetModelDataList_EnsureRegistered, 0 };

void *beActionStarterInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beActionStarterInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beActionStarterInfo_GetMetaObjectFunction,
        "beActionStarterInfo",
        0x20, /* instance size */
        beActionStarterInfo_GetVTable,
        beActionStarterInfo_InitFields,
        0, /* extra callback item */
        g_beActionStarterInfo_callbackList /* callback list */
    );
}

void beActionStarterInfo_GetMetaObjectFunction(void)
{
    beActionStarterInfo_GetMetaObject();
}

static FieldFactory g_beActionStarterInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beActionStarterInfo_fieldTable[] = {
    "_modelList",
};
static igMetaField **g_beActionStarterInfo_fieldHandles[] = {
    &g_beActionStarterInfo_modelListMetaField,
};
static int g_beActionStarterInfo_fieldOffsets[] = {
    28,
};

void beActionStarterInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beActionStarterInfo_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beActionStarterInfo_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beAsTargetModelDataList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beActionStarterInfo_fieldTable, g_beActionStarterInfo_fieldHandles, g_beActionStarterInfo_fieldOffsets, temp_s2);
}

