int FUN_002d01a0(int arg0) {
    FUN_002d02b0();
    return igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586D70), (MemoryPool *)arg0);
}

igMetaObject *igPsx2File_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2File_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002d02b0();
    return g_igPsx2File_metaObject[0];
}

int igPsx2File_GetVTable(void) {
    struct F_2d0230 f;
    int temp_s0;

    igObject_InitHeader((struct ObjectHeader *)&f);
    f.w[1] = 0;
    f.w[2] = 0;
    f.w[9] = 0;
    f.vt = &DAT_0052dc00[0];
    f.w[17] = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
    f.vt = &DAT_0052dc00[0];
    FUN_00130720(&f.w[17], -1);
    FUN_002c0790((igFile *)&f, (short)0);
    return temp_s0;
}

void FUN_002d02b0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2File_Register);
}

void igPsx2File_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPsx2File_metaObject),
        igFile_Register,
        igFile_GetPublishedMetaObject,
        thunk_igPsx2File_GetMetaObject,
        igPsx2File_className,
        0x4C, /* instance size */
        igPsx2File_GetVTable,
        &igPsx2File_InitFields,
        thunk_FUN_0032c0c0, /* extra callback item */
        0 /* callback list */
    );
}

void igPsx2File_InitFields(void) {
    void *temp_a0;
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_00586d70[0]);
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004c1e10[0], 8);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    *(int *)((char *)(temp_s1) + 60) = igUnsignedCharMetaField_GetDefaultDescriptor();
    temp_a0 = ((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 7));
    *(char *)((char *)temp_a0 + 36) = 3;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004c1e30[0], (igMetaField ***)&DAT_004c1e50[0], &DAT_004c1e70[0], temp_s2);
    *(int *)((char *)(DAT_00586d70[0]) + 64) = (int)(&thunk_igFile_GetMetaObject);
}

void thunk_FUN_0032c0c0(void) {
    FUN_0032c0c0();
}

