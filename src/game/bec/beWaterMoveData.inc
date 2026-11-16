igMetaObject *g_beWaterMoveData_metaObject;
igMetaField *g_beWaterMoveData_timeMetaField;
igMetaField *g_beWaterMoveData_powerMetaField;
igMetaField *g_beWaterMoveData_posListMetaField;

void *beWaterMoveData_GetMetaObject(void) {
    igMetaObject *g = g_beWaterMoveData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beWaterMoveData_EnsureRegistered();
    }
    return g_beWaterMoveData_metaObject;
}

int beWaterMoveData_GetVTable(void) {
    union U_340900 u;
    int temp_s0;
    char *ps;
    int *p;
    int v;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_beWaterMoveData_vtable[0];
    ps = &u.b[20];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beWaterMoveData_vtable[0];
    if (ps != 0) {
        p = *(int **)ps;
        if (p != 0) {
            v = p[1] - 1;
            p[1] = v;
            if ((p[1] & 0x7fffff) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    return temp_s0;
}

void beWaterMoveData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beWaterMoveData_Register);
}

static igMetaObjectCallback g_beWaterMoveData_callbackList[] = { igVec3fList_EnsureRegistered, 0 };

void *beWaterMoveData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWaterMoveData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beWaterMoveData_GetMetaObjectFunction,
        "beWaterMoveData",
        0x18, /* instance size */
        beWaterMoveData_GetVTable,
        beWaterMoveData_InitFields,
        0, /* extra callback item */
        g_beWaterMoveData_callbackList /* callback list */
    );
}

void beWaterMoveData_GetMetaObjectFunction(void)
{
    beWaterMoveData_GetMetaObject();
}

static FieldFactory g_beWaterMoveData_ctorTable[] = {
    igLongMetaField_Create,
    igFloatMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beWaterMoveData_fieldTable[] = {
    "_time",
    "_power",
    "_posList",
};
static igMetaField **g_beWaterMoveData_fieldHandles[] = {
    &g_beWaterMoveData_timeMetaField,
    &g_beWaterMoveData_powerMetaField,
    &g_beWaterMoveData_posListMetaField,
};
static int g_beWaterMoveData_fieldOffsets[] = {
    8,
    16,
    20,
};

void beWaterMoveData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beWaterMoveData_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beWaterMoveData_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igVec3fList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beWaterMoveData_fieldTable, g_beWaterMoveData_fieldHandles, g_beWaterMoveData_fieldOffsets, temp_s2);
}

