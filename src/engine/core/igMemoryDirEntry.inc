int igMemoryDirEntry_Create(int arg0) {
    igMemoryDirEntry_EnsureRegistered();
    return igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585F60), (igMemoryPoolView *)arg0);
}

igMetaObject *igMemoryDirEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryDirEntry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryDirEntry_EnsureRegistered();
    return g_igMemoryDirEntry_metaObject[0];
}

int igMemoryDirEntry_GetVTable(void) {
    igMemoryDirEntry entry;
    int temp_s0;
    char *q1;
    int *tv1, *ta1;
    int tc1;
    
    
    igObject_InitHeader((igObject *)&entry);
    entry._vtable = (int)(&g_igNamedObject_vtable[0]);
    q1 = (char *)&entry._name;
    *(int *)q1 = 0;
    entry._vtable = (int)(&DAT_0052f860[0]);
    temp_s0 = *(int *)((char *)&entry + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    entry._vtable = (int)(&g_igNamedObject_vtable[0]);
    if (q1 != 0) {
        tv1 = *(int **)q1;
        if (tv1 != 0) {
            ta1 = tv1 - 2;
            tc1 = tv1[-1] - 1;
            tv1[-1] = tc1;
            if (tc1 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*ta1), (int)ta1);
            }
        }
    }
    return temp_s0;
}

void igMemoryDirEntry_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryDirEntry_Register);
}

void igMemoryDirEntry_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMemoryDirEntry_metaObject),
        igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        igMemoryDirEntry_GetMetaObjectFunction,
        igMemoryDirEntry_className,
        0x38, /* instance size */
        igMemoryDirEntry_GetVTable,
        &igMemoryDirEntry_InitFields,
        0, /* extra callback item */
        g_igMemoryDirEntry_callbackList /* callback list */
    );
}

void igMemoryDirEntry_GetMetaObjectFunction(void) {
    igMemoryDirEntry_GetMetaObject();
}

void igMemoryDirEntry_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igMemoryDirEntry_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igMemoryDirEntry_ctorTable[0], 7);
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    igIntMetaField_SetDefault((void **)temp_v0, -1);
    *(char *)((char *)(temp_v0) + 38) = 0;
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    *(int *)((char *)(temp_s1) + 56) = (int)igMetaField_GetOrCreateMetaObject();
    igObjectRefMetaField_SetDefault((igObjectRefMetaField *)temp_s1, (igObject *)(igCharMetaField_GetDefaultDescriptor()));
    *(char *)((char *)(temp_s1) + 60) = 0;
    *(char *)((char *)(temp_s1) + 38) = 0;
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3))), -1);
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 4))), 1);
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 5))), -1);
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 6))), -1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igMemoryDirEntry_fieldTable[0], (igMetaField ***)&DAT_004c0340[0], &DAT_004c0360[0], temp_s2);
}

