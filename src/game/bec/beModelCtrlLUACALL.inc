igMetaObject *g_beModelCtrlLUACALL_metaObject;
igMetaField *g_beModelCtrlLUACALL_modeNameMetaField;

igMetaObject *beModelCtrlLUACALL_GetMetaObject(void)
{
    igMetaObject *g = g_beModelCtrlLUACALL_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beModelCtrlLUACALL_EnsureRegistered();
    return g_beModelCtrlLUACALL_metaObject;
}

int beModelCtrlLUACALL_GetVTable(void) {
    Obj_3564a0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.m8 = 0;
    obj.vt = &g_beModelCtrlLUACALL_vtable[0];
    obj.m12 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beModelCtrlLUACALL_vtable[0];
    obj.rel12();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.rel8();
    return r;
}

void beModelCtrlLUACALL_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlLUACALL_Register);
}

void *beModelCtrlLUACALL_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlLUACALL_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlLUACALL_GetMetaObjectFunction,
        "beModelCtrlLUACALL",
        0x10, /* instance size */
        beModelCtrlLUACALL_GetVTable,
        beModelCtrlLUACALL_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlLUACALL_GetMetaObjectFunction(void)
{
    beModelCtrlLUACALL_GetMetaObject();
}

static FieldFactory g_beModelCtrlLUACALL_ctorTable[] = {
    igStringMetaField_Create,
};
static const char *g_beModelCtrlLUACALL_fieldTable[] = {
    "_modeName",
};
static igMetaField **g_beModelCtrlLUACALL_fieldHandles[] = {
    &g_beModelCtrlLUACALL_modeNameMetaField,
};
static int g_beModelCtrlLUACALL_fieldOffsets[] = {
    12,
};

void beModelCtrlLUACALL_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlLUACALL_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beModelCtrlLUACALL_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_beModelCtrlLUACALL_fieldTable, g_beModelCtrlLUACALL_fieldHandles, g_beModelCtrlLUACALL_fieldOffsets, temp_s1);
}

