igMetaObject *FUN_002c1fa0(void) {
    if (g_igLocationTable_metaObject[0] == 0) {
        g_igLocationTable_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igLocationTable_metaObject[0];
}

igMetaObject *igLocationTable_GetMetaObject(void)
{
    igMetaObject *g = g_igLocationTable_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c20f0();
    return g_igLocationTable_metaObject[0];
}

int igLocationTable_GetVTable(void) {
    struct W o;
    int *p18;
    int *p17;
    int *p16;
    int r;
    igObject_InitHeader((struct ObjectHeader *)&o);
    o.vt = &DAT_0052fc50[0];
    p16 = &o.f[3];
    *p16 = 0;
    p17 = &o.f[4];
    *p17 = 0;
    p18 = &o.f[5];
    *p18 = 0;
    o.f[6] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o.vt = &DAT_0052fc50[0];
    FUN_002b8740((ObjectRefWord *)&o.f[6], -1);
    FUN_002b8740((ObjectRefWord *)p18, -1);
    FUN_002b86c0((void **)p17, -1);
    FUN_002b8640((ObjectRefWord *)p16, -1);
    return r;
}

void FUN_002c20f0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igLocationTable_Register);
}

void igLocationTable_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igLocationTable_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igLocationTable_GetMetaObject,
        igLocationTable_className,
        0x20, /* instance size */
        igLocationTable_GetVTable,
        &igLocationTable_InitFields,
        0, /* extra callback item */
        g_igLocationTable_callbackList /* callback list */
    );
}

void thunk_igLocationTable_GetMetaObject(void) {
    igLocationTable_GetMetaObject();
}

void igLocationTable_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)g_igLocationTable_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, (igMetaField * (**)(void *))&g_igLocationTable_ctorTable[0], 6);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_002ca2a0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_002ca8f0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_002b8d90();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_002b8d90();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, (const char **)&g_igLocationTable_fieldTable[0], (igMetaField ***)&DAT_004c0560[0], &DAT_004c0580[0], temp_s0);
}

