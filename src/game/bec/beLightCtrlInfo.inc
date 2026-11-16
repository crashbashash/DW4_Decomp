igMetaObject *g_beLightCtrlInfo_metaObject;
igMetaField *g_beLightCtrlInfo_lightSetListMetaField;

void *beLightCtrlInfo_GetMetaObject(void) {
    igMetaObject *g = g_beLightCtrlInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beLightCtrlInfo_EnsureRegistered();
    }
    return g_beLightCtrlInfo_metaObject;
}

int beLightCtrlInfo_GetVTable(void) {
    struct W_35bd50 o;
    int r;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[4] = 0;
    o.f[5] = 0;
    o.vt = g_beLightCtrlInfo_vtable;
    o.f[6] = 0;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_beLightCtrlInfo_vtable;
    FUN_0035bdd0((struct R **)(&o.f[6]), (short)(-1));
    FUN_0033ec80((struct S_33ec80 *)&o, (short)0);
    return r;
}

struct R **FUN_0035bdd0(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void beLightCtrlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLightCtrlInfo_Register);
}

static igMetaObjectCallback g_beLightCtrlInfo_callbackList[] = { igLightSetList_EnsureRegistered, 0 };

void *beLightCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLightCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beLightCtrlInfo_GetMetaObjectFunction,
        "beLightCtrlInfo",
        0x20, /* instance size */
        beLightCtrlInfo_GetVTable,
        beLightCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beLightCtrlInfo_callbackList /* callback list */
    );
}

void beLightCtrlInfo_GetMetaObjectFunction(void)
{
    beLightCtrlInfo_GetMetaObject();
}

static FieldFactory g_beLightCtrlInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beLightCtrlInfo_fieldTable[] = {
    "_lightSetList",
};
static igMetaField **g_beLightCtrlInfo_fieldHandles[] = {
    &g_beLightCtrlInfo_lightSetListMetaField,
};
static int g_beLightCtrlInfo_fieldOffsets[] = {
    28,
};

void beLightCtrlInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beLightCtrlInfo_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beLightCtrlInfo_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igLightSetList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beLightCtrlInfo_fieldTable, g_beLightCtrlInfo_fieldHandles, g_beLightCtrlInfo_fieldOffsets, temp_s2);
}

igMetaEnum *g_beLightCtrlInfo_msgActionMetaEnum;
static const char *g_beLightCtrlInfo_msgActionNames[] = {
    "SETCOLOR",
};
static int g_beLightCtrlInfo_msgActionValues[] = {
    0,
};

igMetaEnum *FUN_0035bfb0(void) {
    if (g_beLightCtrlInfo_msgActionMetaEnum == 0) {
        g_beLightCtrlInfo_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_beLightCtrlInfo_msgActionNames, g_beLightCtrlInfo_msgActionValues, 1);
    }
    return g_beLightCtrlInfo_msgActionMetaEnum;
}

