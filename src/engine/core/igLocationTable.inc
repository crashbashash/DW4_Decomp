igMetaObject *igLocationTable_GetOrCreateMetaObject(void) {
    if (g_igLocationTable_metaObject[0] == 0) {
        g_igLocationTable_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igLocationTable_metaObject[0];
}

igMetaObject *igLocationTable_GetMetaObject(void)
{
    igMetaObject *g = g_igLocationTable_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igLocationTable_EnsureRegistered();
    return g_igLocationTable_metaObject[0];
}

int igLocationTable_GetVTable(void) {
    igLocationTable o;
    int *p18;
    int *p17;
    int *p16;
    int r;
    igObject_InitHeader((igObject *)&o);
    o._vtable = (int)&DAT_0052fc50[0];
    p16 = &o._locations;
    *p16 = 0;
    p17 = &o._hashIndex;
    *p17 = 0;
    p18 = &o._symbolNames;
    *p18 = 0;
    o._sourceFileNames = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o._vtable = (int)&DAT_0052fc50[0];
    igSmartPointer_igStringTable_Destruct((igSmartPointer<igObject> *)&o._sourceFileNames, -1);
    igSmartPointer_igStringTable_Destruct((igSmartPointer<igObject> *)p18, -1);
    igSmartPointer_igIntListNoClean_Destruct((void **)p17, -1);
    igSmartPointer_igUnsignedIntListNoClean_Destruct((igSmartPointer<igObject> *)p16, -1);
    return r;
}

void igLocationTable_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igLocationTable_Register);
}

void igLocationTable_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igLocationTable_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igLocationTable_GetMetaObjectFunction,
        igLocationTable_className,
        0x20, /* instance size */
        igLocationTable_GetVTable,
        &igLocationTable_InitFields,
        0, /* extra callback item */
        g_igLocationTable_callbackList /* callback list */
    );
}

void igLocationTable_GetMetaObjectFunction(void) {
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
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igUnsignedIntListNoClean_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igIntListNoClean_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, (const char **)&g_igLocationTable_fieldTable[0], (igMetaField ***)&DAT_004c0560[0], &DAT_004c0580[0], temp_s0);
}

