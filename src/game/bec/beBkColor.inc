void beBkColor_CreateInstance(int arg0) {
    FUN_00369f80();
    igMetaObject_CreateInstance(*(int *)0x589D10, arg0);
}

igMetaObject *FUN_00369e00(void) {
    if (g_beBkColor_metaObject[0] == 0) {
        g_beBkColor_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beBkColor_metaObject[0];
}

void *FUN_00369e50(void) {
    igMetaObject *g = g_beBkColor_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00369f80();
    }
    return g_beBkColor_metaObject[0];
}

int beBkColor_GetVTable(void) {
    union U_369ea0 u;
    int temp_s1;
    void **q2;
    void **q3;
    int *temp_a1;
    int temp_v0_2;
    void *temp_a0;
    void *temp_v1_2;

    igObject_InitHeader(u.b);
    q2 = &u.p[2];
    *q2 = 0;
    u.w[0] = (int)(&DAT_0053a0d0[0]);
    q3 = &u.p[6];
    *q3 = 0;
    u.w[0] = (int)(&DAT_0053a170[0]);
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_0053a0d0[0]);
    if (q3 != 0) {
        temp_a0 = *q3;
        if (temp_a0 != 0) {
            ((igObject *)temp_a0)->_refCount = (int)((int) (((igObject *)temp_a0)->_refCount - 1));
            if (((unsigned long long) ((long long) (int) ((igObject *)temp_a0)->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    if (q2 != 0) {
        temp_v1_2 = *q2;
        if (temp_v1_2 != 0) {
            temp_a1 = (int *)((char *)temp_v1_2 - 8);
            temp_v0_2 = *(int *)((char *)(temp_v1_2) - 4) - 1;
            *(int *)((char *)(temp_v1_2) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s1;
}

void FUN_00369f80(void)
{
    igMetaObject_RunStaticInit(beBkColor_Register);
}

void *beBkColor_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beBkColor_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beBkColor_GetMetaObject,
        beBkColor_className,
        0x24, /* instance size */
        beBkColor_GetVTable,
        beBkColor_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beBkColor_GetMetaObject(void)
{
    FUN_00369e50();
}

void beBkColor_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beBkColor_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beBkColor_ctorTable[0], 1);
    igMetaObject_NameFields(temp_s0, &g_beBkColor_fieldTable[0], &DAT_004c7b88[0], &DAT_004c7b90[0], temp_s1);
}

