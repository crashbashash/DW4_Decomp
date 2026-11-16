igMetaObject *g_igVertexArray2Helper_metaObject;
igMetaField *g_igVertexArray2Helper_vertexArrayMetaField;

void FUN_0014a4d0(int arg0) {
    FUN_0014a640();
    igMetaObject_CreateInstance(g_igVertexArray2Helper_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igVertexArray2Helper_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexArray2Helper_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014a640();
    return g_igVertexArray2Helper_metaObject;
}

int igVertexArray2Helper_GetVTable(void) {
    Obj_14a560 obj;
    int r;

    igObject_InitHeader((igObject *)&obj);
    obj.m8 = 0;
    obj.vt = &g_igVertexArray2Helper_vtable[0];
    obj.m12 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj.vt = &g_igVertexArray2Helper_vtable[0];
    obj.rel12();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.rel8();
    return r;
}

void FUN_0014a640(void)
{
    igMetaObject_RunStaticInit(igVertexArray2Helper_Register);
}

static igMetaObjectCallback g_igVertexArray2Helper_callbackList[] = { FUN_0014ab70, 0 };

CallbackArray *igVertexArray2Helper_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVertexArray2Helper_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igVertexArray2Helper_GetMetaObject,
        "igVertexArray2Helper",
        0x10, /* instance size */
        igVertexArray2Helper_GetVTable,
        &igVertexArray2Helper_InitFields,
        0, /* extra callback item */
        g_igVertexArray2Helper_callbackList /* callback list */
    );
}

void thunk_igVertexArray2Helper_GetMetaObject(void) {
    igVertexArray2Helper_GetMetaObject();
}

int FUN_0014a6e0(void) {
    return (int)g_igNamedObject_metaObject;
}

static FieldFactory g_igVertexArray2Helper_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igVertexArray2Helper_fieldTable[] = {
    "_vertexArray",
};
static igMetaField **g_igVertexArray2Helper_fieldHandles[] = {
    &g_igVertexArray2Helper_vertexArrayMetaField,
};
static int g_igVertexArray2Helper_fieldOffsets[] = {
    12,
};

void igVertexArray2Helper_InitFields(void) {
    int fieldStart;
    void *temp_s1;
    igMetaObject *meta;

    meta = g_igVertexArray2Helper_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igVertexArray2Helper_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0014a7c0();
    igMetaObject_NameFields(meta, g_igVertexArray2Helper_fieldTable, g_igVertexArray2Helper_fieldHandles, g_igVertexArray2Helper_fieldOffsets, fieldStart);
}

