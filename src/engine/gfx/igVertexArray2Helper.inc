void FUN_0014a4d0(int arg0) {
    FUN_0014a640();
    igMetaObject_CreateInstance(*(int *)0x55F9D0, arg0);
}

igMetaObject *igVertexArray2Helper_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexArray2Helper_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014a640();
    return g_igVertexArray2Helper_metaObject[0];
}

int igVertexArray2Helper_GetVTable(void) {
    Obj_14a560 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.m8 = 0;
    obj.vt = &DAT_005262a0[0];
    obj.m12 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_005262a0[0];
    obj.rel12();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.rel8();
    return r;
}

void FUN_0014a640(void)
{
    igMetaObject_RunStaticInit(igVertexArray2Helper_Register);
}

void igVertexArray2Helper_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVertexArray2Helper_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igVertexArray2Helper_GetMetaObject,
        igVertexArray2Helper_className,
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
    return g_igNamedObject_metaObject[0];
}

void igVertexArray2Helper_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igVertexArray2Helper_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004884f0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0014a7c0();
    igMetaObject_NameFields(temp_s0, &DAT_004884f8[0], &DAT_00488500[0], &DAT_00488508[0], temp_s2);
}

