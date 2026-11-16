igMetaObject *g_beMatCtrlInfo_metaObject;
igMetaField *g_beMatCtrlInfo_switchgraphMetaField;
igMetaField *g_beMatCtrlInfo_dataListMetaField;
igMetaField *g_beMatCtrlInfo_searchMetaField;

void *beMatCtrlInfo_GetMetaObject(void) {
    igMetaObject *g = g_beMatCtrlInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMatCtrlInfo_EnsureRegistered();
    }
    return g_beMatCtrlInfo_metaObject;
}

int beMatCtrlInfo_GetVTable(void) {
    struct Obj_359b20 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.vt = &g_beMatCtrlInfo_vtable[0];
    obj.w[6] = 0;
    obj.w[7] = 0;
    obj.w[8] = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beMatCtrlInfo_vtable[0];
    FUN_00359c50((void **)(&obj.w[8]), (short)(-1));
    FUN_00359bd0((void **)(&obj.w[7]), (long long)(-1));
    FUN_00343260((ObjectRefWord *)(&obj.w[6]), -1);
    FUN_0033ec80((struct S_33ec80 *)((int *)&obj), (short)0);
    return t;
}

void **FUN_00359bd0(void **arg0, long long arg1) {
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

void **FUN_00359c50(void **arg0, short arg1) {
    S_temp_a0_359c50 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_359c50 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void beMatCtrlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMatCtrlInfo_Register);
}

static igMetaObjectCallback g_beMatCtrlInfo_callbackList[] = { igSwitch_EnsureRegistered, beMatCtrlDataList_EnsureRegistered, beMatCtrlSearchList_EnsureRegistered, 0 };

void *beMatCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMatCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beMatCtrlInfo_GetMetaObjectFunction,
        "beMatCtrlInfo",
        0x28, /* instance size */
        beMatCtrlInfo_GetVTable,
        beMatCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beMatCtrlInfo_callbackList /* callback list */
    );
}

void beMatCtrlInfo_GetMetaObjectFunction(void)
{
    beMatCtrlInfo_GetMetaObject();
}

static FieldFactory g_beMatCtrlInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beMatCtrlInfo_fieldTable[] = {
    "_switchgraph",
    "_dataList",
    "_search",
};
static igMetaField **g_beMatCtrlInfo_fieldHandles[] = {
    &g_beMatCtrlInfo_switchgraphMetaField,
    &g_beMatCtrlInfo_dataListMetaField,
    &g_beMatCtrlInfo_searchMetaField,
};
static int g_beMatCtrlInfo_fieldOffsets[] = {
    28,
    32,
    36,
};

void beMatCtrlInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_beMatCtrlInfo_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beMatCtrlInfo_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igSwitch_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)beMatCtrlDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)beMatCtrlSearchList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beMatCtrlInfo_fieldTable, g_beMatCtrlInfo_fieldHandles, g_beMatCtrlInfo_fieldOffsets, temp_s2);
}

