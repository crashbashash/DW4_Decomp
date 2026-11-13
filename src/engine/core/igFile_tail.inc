int FUN_002c4be0(void) {
    if (DAT_005863a0[0] == 0) {
        DAT_005863a0[0] = ((int)igMetaEnum_Create((char *)(&text_ReadMode[0]), (char **)(&DAT_004c0ae8[0]), &DAT_004c0af8[0], 3));
    }
    return DAT_005863a0[0];
}

int FUN_002c4c40(void) {
    if (DAT_005863a8[0] == 0) {
        DAT_005863a8[0] = ((int)igMetaEnum_Create((char *)(&text_OpenMode[0]), (char **)(&DAT_004c0b10[0]), &DAT_004c0b40[0], 9));
    }
    return DAT_005863a8[0];
}

void * igFile_Create(int arg0) {
    FUN_002c4d80();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x5863B0), (MemoryPool *)arg0));
}

igMetaObject *FUN_002c4ce0(void) {
    if (g_igFile_metaObject[0] == 0) {
        g_igFile_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igFile_metaObject[0];
}

igMetaObject *igFile_GetMetaObject(void)
{
    igMetaObject *g = g_igFile_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c4d80();
    return g_igFile_metaObject[0];
}

void FUN_002c4d80(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igFile_Register);
}

void igFile_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igFile_metaObject),
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igFile_GetMetaObject,
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
    FUN_002dc7a0((igEnumMetaFieldView *)temp_v0, (const int *)&DAT_004c0bf0[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_002c4be0);
    temp_v0_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    FUN_002dc7a0((igEnumMetaFieldView *)temp_v0_2, (const int *)&DAT_004c0bf8[0]);
    *(int *)((char *)(temp_v0_2) + 52) = (int)(&FUN_002c4c40);
    *(char *)((char *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3))) + 38) = 0;
    FUN_002ea4b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 4))), 0x100000);
    FUN_002ea4b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 5))), 0x100000);
    FUN_002ea4b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 6))), 0x1000);
    *(char *)((char *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 7))) + 38) = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igFile_fieldTable[0], (igMetaField ***)&DAT_004c0bb0[0], &DAT_004c0bd0[0], temp_s2);
    *(int *)((char *)(((void * *)g_igFile_metaObject)[0]) + 60) = (int)(&thunk_igPsx2File_GetMetaObject);
}

