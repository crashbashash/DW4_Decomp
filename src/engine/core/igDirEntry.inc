int FUN_002c7720(void) {
    if (DAT_00586700[0] == 0) {
        DAT_00586700[0] = ((int)igMetaEnum_Create((char *)&text_RefType[0], (char **)&DAT_004c1248[0], &DAT_004c1258[0], 3));
    }
    return DAT_00586700[0];
}

int FUN_002c7780(void) {
    if (DAT_00586708[0] == 0) {
        DAT_00586708[0] = ((int)igMetaEnum_Create((char *)&text_ResolveMethod[0], (char **)&DAT_004c1268[0], &DAT_004c1278[0], 3));
    }
    return DAT_00586708[0];
}

void * FUN_002c77e0(int arg0) {
    FUN_002c7900();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586710), (MemoryPool *)arg0));
}

igMetaObject *igDirEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igDirEntry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c7900();
    return g_igDirEntry_metaObject[0];
}

int igDirEntry_GetVTable(void) {
    union U_2c7870 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;
    igObject_InitHeader((ObjectHeader *)u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_00530900[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(((void * *)g_objectSystem)[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_002c7900(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDirEntry_Register);
}

void igDirEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igDirEntry_metaObject),
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igDirEntry_GetMetaObject,
        igDirEntry_className,
        0x1C, /* instance size */
        igDirEntry_GetVTable,
        &igDirEntry_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igDirEntry_GetMetaObject(void) {
    igDirEntry_GetMetaObject();
}

void igDirEntry_InitFields(void) {
    int temp_s2;
    void *temp_v0_3;
    void *temp_v0_2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)g_igDirEntry_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igDirEntry_ctorTable[0], 4);
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    FUN_002ea4b0((void **)temp_v0, -1);
    ((igIntMetaField *)temp_v0)->_persistent = 0;
    temp_v0_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    FUN_002dc7a0((igEnumMetaFieldView *)temp_v0_2, (const int *)&DAT_004c12d0[0]);
    ((igEnumMetaField *)temp_v0_2)->_persistent = 0;
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(&FUN_002c7780);
    temp_v0_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    FUN_002dc7a0((igEnumMetaFieldView *)temp_v0_3, (const int *)&DAT_004c12d8[0]);
    ((igEnumMetaField *)temp_v0_3)->_persistent = 0;
    ((igEnumMetaField *)temp_v0_3)->_getMetaEnumFunction = (int)(FUN_002c7720);
    *(char *)((char *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3))) + 38) = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igDirEntry_fieldTable[0], (igMetaField ***)&DAT_004c12b0[0], &DAT_004c12c0[0], temp_s2);
}

