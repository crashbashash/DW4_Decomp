void igEnumArrayMetaField_Create(int arg0) {
    igEnumArrayMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5865B0), (igMemoryPoolView *)arg0);
}

igMetaObject *igEnumArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igEnumArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igEnumArrayMetaField_EnsureRegistered();
    return g_igEnumArrayMetaField_metaObject[0];
}

int igEnumArrayMetaField_GetVTable(void) {
    igEnumArrayMetaField u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igEnumMetaField_Init((int **)&u);
    u._vtable = (int)&DAT_005304f0[0];
    temp_s0 = *(int *)((char *)&u + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    u._vtable = (int)&g_igMetaField_vtable[0];
    ps = (char *)&u._fieldName;
    if (ps != 0) {
        temp_v1 = *(int **)ps;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return temp_s0;
}

void igEnumArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igEnumArrayMetaField_Register);
}

void igEnumArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igEnumArrayMetaField_metaObject),
        igEnumMetaField_Register,
        igEnumMetaField_GetPublishedMetaObject,
        igEnumArrayMetaField_GetMetaObjectFunction,
        igEnumArrayMetaField_className,
        0x3C, /* instance size */
        igEnumArrayMetaField_GetVTable,
        &igEnumArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igEnumArrayMetaField_callbackList /* callback list */
    );
}

void igEnumArrayMetaField_GetMetaObjectFunction(void) {
    igEnumArrayMetaField_GetMetaObject();
}

igMetaObject *igEnumMetaField_GetPublishedMetaObject(void) {
    return g_igEnumMetaField_metaObject[0];
}

void igEnumArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igEnumArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igEnumArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igEnumArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004c0fa8[0], &DAT_004c0fb0[0], temp_s1);
}

void igEnumArrayMetaField_CreateDefaultDescriptor(void) {
    int *s0;
    int *g;

    if (g_igEnumArrayMetaField_descriptor[0] == 0) {
        g_igEnumArrayMetaField_descriptor[0] = ((int *)igMetaObject_CreateInstance((igMetaObject *)g_igEnumArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        s0 = g_igEnumArrayMetaField_descriptor[0];
        if (s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)s0);
            g = g_igEnumArrayMetaField_descriptor[0];
            g[1] = g[1] - 1;
            if ((g[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(g);
            }
            *(short *)((char *)g_igEnumArrayMetaField_descriptor[0] + 18) = (short)(((int *)igMetaField_GetMetaFieldList())[3] - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igEnumArrayMetaField_descriptor[0]);
        }
    }
}

