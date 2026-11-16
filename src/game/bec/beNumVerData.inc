igMetaObject *g_beNumVerData_metaObject;
igMetaField *g_beNumVerData_dispMetaField;
igMetaField *g_beNumVerData_verDataListMetaField;

void *beNumVerData_GetMetaObject(void) {
    igMetaObject *g = g_beNumVerData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNumVerData_EnsureRegistered();
    }
    return g_beNumVerData_metaObject;
}

int beNumVerData_GetVTable(void) {
    struct Obj_34dad0 obj;
    char *o;
    int t;

    igObject_InitHeader(&obj);
    obj.vt = &g_beNumVerData_vtable[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNumVerData_vtable[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}

void beNumVerData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNumVerData_Register);
}

static igMetaObjectCallback g_beNumVerData_callbackList[] = { beNumVerInsideDataList_EnsureRegistered, 0 };

void *beNumVerData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNumVerData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNumVerData_GetMetaObjectFunction,
        "beNumVerData",
        0x10, /* instance size */
        beNumVerData_GetVTable,
        beNumVerData_InitFields,
        0, /* extra callback item */
        g_beNumVerData_callbackList /* callback list */
    );
}

void beNumVerData_GetMetaObjectFunction(void)
{
    beNumVerData_GetMetaObject();
}

static FieldFactory g_beNumVerData_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNumVerData_fieldTable[] = {
    "_disp",
    "_verDataList",
};
static igMetaField **g_beNumVerData_fieldHandles[] = {
    &g_beNumVerData_dispMetaField,
    &g_beNumVerData_verDataListMetaField,
};
static int g_beNumVerData_fieldOffsets[] = {
    8,
    12,
};

void beNumVerData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNumVerData_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNumVerData_ctorTable, 2);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2), -1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beNumVerInsideDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beNumVerData_fieldTable, g_beNumVerData_fieldHandles, g_beNumVerData_fieldOffsets, temp_s2);
}

