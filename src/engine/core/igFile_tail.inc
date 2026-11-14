int igFile_GetReadModeMetaEnum(void) {
    if (DAT_005863a0[0] == 0) {
        DAT_005863a0[0] = ((int)igMetaEnum_Create((char *)(&text_ReadMode[0]), (char **)(&DAT_004c0ae8[0]), &DAT_004c0af8[0], 3));
    }
    return DAT_005863a0[0];
}

int igFile_GetOpenModeMetaEnum(void) {
    if (DAT_005863a8[0] == 0) {
        DAT_005863a8[0] = ((int)igMetaEnum_Create((char *)(&text_OpenMode[0]), (char **)(&DAT_004c0b10[0]), &DAT_004c0b40[0], 9));
    }
    return DAT_005863a8[0];
}

void * igFile_Create(int arg0) {
    igFile_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5863B0), (igMemoryPoolView *)arg0));
}

igMetaObject *igFile_GetOrCreateMetaObject(void) {
    if (g_igFile_metaObject[0] == 0) {
        g_igFile_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igFile_metaObject[0];
}

igMetaObject *igFile_GetMetaObject(void)
{
    igMetaObject *g = g_igFile_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFile_EnsureRegistered();
    return g_igFile_metaObject[0];
}

void igFile_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igFile_Register);
}

void igFile_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igFile_metaObject),
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        igFile_GetMetaObjectFunction,
        igFile_className,
        0x2C, /* instance size */
        0,
        &igFile_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igFile_InitFields(void) {
    int temp_s2;
    void *temp_v0_2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)(((void * *)g_igFile_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igFile_ctorTable[0], 8);
    igStringMetaField_SetDefaultText((int *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2))), (int)&text_DefaultFileName[0]);
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)temp_v0, (const int *)&DAT_004c0bf0[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&igFile_GetReadModeMetaEnum);
    temp_v0_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)temp_v0_2, (const int *)&DAT_004c0bf8[0]);
    *(int *)((char *)(temp_v0_2) + 52) = (int)(&igFile_GetOpenModeMetaEnum);
    *(char *)((char *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3))) + 38) = 0;
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 4))), 0x100000);
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 5))), 0x100000);
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 6))), 0x1000);
    *(char *)((char *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 7))) + 38) = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igFile_fieldTable[0], (igMetaField ***)&DAT_004c0bb0[0], &DAT_004c0bd0[0], temp_s2);
    *(int *)((char *)(((void * *)g_igFile_metaObject)[0]) + 60) = (int)(&igPsx2File_GetMetaObjectFunction);
}

