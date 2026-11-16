igMetaObject *g_beNumberCtrlInfoWork_metaObject;
igMetaField *g_beNumberCtrlInfoWork_dispNumMetaField;
igMetaField *g_beNumberCtrlInfoWork_realNumMetaField;
igMetaField *g_beNumberCtrlInfoWork_changeNumMetaField;

void beNumberCtrlInfoWork_Create(int arg0) {
    beNumberCtrlInfoWork_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588630, arg0);
}

igMetaObject *beNumberCtrlInfoWork_GetOrCreateMetaObject(void) {
    if (g_beNumberCtrlInfoWork_metaObject == 0) {
        g_beNumberCtrlInfoWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNumberCtrlInfoWork_metaObject;
}

igMetaObject *beNumberCtrlInfoWork_GetMetaObject(void) {
    igMetaObject *g = g_beNumberCtrlInfoWork_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beNumberCtrlInfoWork_EnsureRegistered();
    return g_beNumberCtrlInfoWork_metaObject;
}

int beNumberCtrlInfoWork_GetVTable(void) {
    int obj[8];

    igObject_InitHeader(obj);
    obj[0] = (int)&g_beNumberCtrlInfoWork_vtable[0];
    return *(int *)((char *)obj + *(int *)((char *)g_objectSystem[0] + 916));
}

void beNumberCtrlInfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNumberCtrlInfoWork_Register);
}

void *beNumberCtrlInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNumberCtrlInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNumberCtrlInfoWork_GetMetaObjectFunction,
        "beNumberCtrlInfoWork",
        0x14, /* instance size */
        beNumberCtrlInfoWork_GetVTable,
        beNumberCtrlInfoWork_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNumberCtrlInfoWork_GetMetaObjectFunction(void)
{
    beNumberCtrlInfoWork_GetMetaObject();
}

static FieldFactory g_beNumberCtrlInfoWork_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNumberCtrlInfoWork_fieldTable[] = {
    "_dispNum",
    "_realNum",
    "_changeNum",
};
static igMetaField **g_beNumberCtrlInfoWork_fieldHandles[] = {
    &g_beNumberCtrlInfoWork_dispNumMetaField,
    &g_beNumberCtrlInfoWork_realNumMetaField,
    &g_beNumberCtrlInfoWork_changeNumMetaField,
};
static int g_beNumberCtrlInfoWork_fieldOffsets[] = {
    8,
    12,
    16,
};

void beNumberCtrlInfoWork_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNumberCtrlInfoWork_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNumberCtrlInfoWork_ctorTable, 3);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1)), -1);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1)), -1);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)), -1);
    igMetaObject_NameFields(temp_s0, g_beNumberCtrlInfoWork_fieldTable, g_beNumberCtrlInfoWork_fieldHandles, g_beNumberCtrlInfoWork_fieldOffsets, temp_s1);
}

