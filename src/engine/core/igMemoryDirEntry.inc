int FUN_002c0d80(int arg0) {
    FUN_002c0ea0();
    return igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585F60), (MemoryPool *)arg0);
}

igMetaObject *igMemoryDirEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryDirEntry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c0ea0();
    return g_igMemoryDirEntry_metaObject[0];
}

int igMemoryDirEntry_GetVTable(void) {
    union U_2c0e10 u;
    int temp_s0;
    char *q1;
    int *tv1, *ta1;
    int tc1;
    
    
    igObject_InitHeader((ObjectHeader *)u.b);
    u.w[0] = (int)(&DAT_00524950[0]);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&DAT_0052f860[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(((void * *)g_objectSystem)[0]) + 916)];
    u.w[0] = (int)(&DAT_00524950[0]);
    if (q1 != 0) {
        tv1 = *(int **)q1;
        if (tv1 != 0) {
            ta1 = tv1 - 2;
            tc1 = tv1[-1] - 1;
            tv1[-1] = tc1;
            if (tc1 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*ta1), (int)ta1);
            }
        }
    }
    return temp_s0;
}

void FUN_002c0ea0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryDirEntry_Register);
}

void igMemoryDirEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMemoryDirEntry_metaObject),
        igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        thunk_igMemoryDirEntry_GetMetaObject,
        igMemoryDirEntry_className,
        0x38, /* instance size */
        igMemoryDirEntry_GetVTable,
        &igMemoryDirEntry_InitFields,
        0, /* extra callback item */
        g_igMemoryDirEntry_callbackList /* callback list */
    );
}

void thunk_igMemoryDirEntry_GetMetaObject(void) {
    igMemoryDirEntry_GetMetaObject();
}

void igMemoryDirEntry_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igMemoryDirEntry_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004c0300[0], 7);
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    FUN_002ea4b0((void **)temp_v0, -1);
    *(char *)((char *)(temp_v0) + 38) = 0;
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_002beca0();
    FUN_00303460((igObjectRefMetaField *)temp_s1, (igObject *)(FUN_002cc2c0()));
    *(char *)((char *)(temp_s1) + 60) = 0;
    *(char *)((char *)(temp_s1) + 38) = 0;
    FUN_002ea4b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3))), -1);
    FUN_002d3890((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 4))), 1);
    FUN_002ea4b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 5))), -1);
    FUN_002ea4b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 6))), -1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004c0320[0], (igMetaField ***)&DAT_004c0340[0], &DAT_004c0360[0], temp_s2);
}

