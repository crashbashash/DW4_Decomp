int FUN_002d01a0(int arg0) {
    FUN_002d02b0();
    return igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586D70), (igMemoryPoolView *)arg0);
}

igMetaObject *igPsx2File_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2File_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002d02b0();
    return g_igPsx2File_metaObject[0];
}

int igPsx2File_GetVTable(void) {
    igPsx2File f;
    int temp_s0;

    igObject_InitHeader((igObject *)&f);
    f._name = 0;
    f._fileName = 0;
    f._completeFilename = 0;
    f._vtable = (int)&DAT_0052dc00[0];
    f._prefix = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    f._vtable = (int)&DAT_0052dc00[0];
    FUN_00130720(&f._prefix, -1);
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

    temp_s0 = (void *)(g_igPsx2File_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igPsx2File_ctorTable[0], 8);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    *(int *)((char *)(temp_s1) + 60) = igUnsignedCharMetaField_GetDefaultDescriptor();
    temp_a0 = ((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 7));
    *(char *)((char *)temp_a0 + 36) = 3;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igPsx2File_fieldTable[0], (igMetaField ***)&DAT_004c1e50[0], &DAT_004c1e70[0], temp_s2);
    *(int *)((char *)(g_igPsx2File_metaObject[0]) + 64) = (int)(&thunk_igFile_GetMetaObject);
}

void thunk_FUN_0032c0c0(void) {
    FUN_0032c0c0();
}

