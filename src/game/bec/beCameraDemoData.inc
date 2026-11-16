igMetaObject *g_beCameraDemoData_metaObject;
igMetaField *g_beCameraDemoData_cameraPathMetaField;
igMetaField *g_beCameraDemoData_endTimeMetaField;
igMetaField *g_beCameraDemoData_totalSecMetaField;

void *beCameraDemoData_GetMetaObject(void) {
    bool ok;
    if (g_beCameraDemoData_metaObject == 0) goto make;
    ok = !!(g_beCameraDemoData_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beCameraDemoData_EnsureRegistered();
done:;
    return g_beCameraDemoData_metaObject;
}

int beCameraDemoData_GetVTable(void) {
    Obj_368fd0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &g_beCameraDemoData_vtable[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beCameraDemoData_vtable[0];
    obj.release();
    return r;
}

void beCameraDemoData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCameraDemoData_Register);
}

static igMetaObjectCallback g_beCameraDemoData_callbackList[] = { igGraphPath_EnsureRegistered, 0 };

void *beCameraDemoData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCameraDemoData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCameraDemoData_GetMetaObjectFunction,
        "beCameraDemoData",
        0x20, /* instance size */
        beCameraDemoData_GetVTable,
        beCameraDemoData_InitFields,
        0, /* extra callback item */
        g_beCameraDemoData_callbackList /* callback list */
    );
}

void beCameraDemoData_GetMetaObjectFunction(void)
{
    beCameraDemoData_GetMetaObject();
}

static FieldFactory g_beCameraDemoData_ctorTable[] = {
    igObjectRefMetaField_Create,
    igLongMetaField_Create,
    igFloatMetaField_Create,
};
static const char *g_beCameraDemoData_fieldTable[] = {
    "_cameraPath",
    "_endTime",
    "_totalSec",
};
static igMetaField **g_beCameraDemoData_fieldHandles[] = {
    &g_beCameraDemoData_cameraPathMetaField,
    &g_beCameraDemoData_endTimeMetaField,
    &g_beCameraDemoData_totalSecMetaField,
};
static int g_beCameraDemoData_fieldOffsets[] = {
    8,
    16,
    24,
};

void beCameraDemoData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beCameraDemoData_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beCameraDemoData_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igGraphPath_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beCameraDemoData_fieldTable, g_beCameraDemoData_fieldHandles, g_beCameraDemoData_fieldOffsets, temp_s2);
}

