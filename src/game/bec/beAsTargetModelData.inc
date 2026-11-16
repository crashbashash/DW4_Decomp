igMetaObject *g_beAsTargetModelData_metaObject;
igMetaField *g_beAsTargetModelData_dataListMetaField;

void *beAsTargetModelData_GetMetaObject(void) {
    igMetaObject *g = g_beAsTargetModelData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beAsTargetModelData_EnsureRegistered();
    }
    return g_beAsTargetModelData_metaObject;
}

int beAsTargetModelData_GetVTable(void) {
    union U_36b7e0 u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;
    int *q8;
    int *q12;

    igObject_InitHeader(u.b);
    q8 = (int *)&u.b[8];
    *q8 = 0;
    u.vt = (int)&g_beAsTargetModelData_vtable[0];
    q12 = (int *)&u.b[12];
    *q12 = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beAsTargetModelData_vtable[0];
    if (q12 != 0) {
        o = (char *)*q12;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q8 != 0) {
        temp_v1 = (int *)*q8;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return t;
}

void beAsTargetModelData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAsTargetModelData_Register);
}

static igMetaObjectCallback g_beAsTargetModelData_callbackList[] = { beActionStarterDataList_EnsureRegistered, 0 };

void *beAsTargetModelData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAsTargetModelData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAsTargetModelData_GetMetaObjectFunction,
        "beAsTargetModelData",
        0x10, /* instance size */
        beAsTargetModelData_GetVTable,
        beAsTargetModelData_InitFields,
        0, /* extra callback item */
        g_beAsTargetModelData_callbackList /* callback list */
    );
}

void beAsTargetModelData_GetMetaObjectFunction(void)
{
    beAsTargetModelData_GetMetaObject();
}

static FieldFactory g_beAsTargetModelData_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beAsTargetModelData_fieldTable[] = {
    "_dataList",
};
static igMetaField **g_beAsTargetModelData_fieldHandles[] = {
    &g_beAsTargetModelData_dataListMetaField,
};
static int g_beAsTargetModelData_fieldOffsets[] = {
    12,
};

void beAsTargetModelData_InitFields(void) {
    int base;
    void *dataList;
    void *meta;

    meta = (void *)g_beAsTargetModelData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beAsTargetModelData_ctorTable, 1);
    dataList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)dataList)->_metaObject = (int)beActionStarterDataList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beAsTargetModelData_fieldTable, g_beAsTargetModelData_fieldHandles, g_beAsTargetModelData_fieldOffsets, base);
}

