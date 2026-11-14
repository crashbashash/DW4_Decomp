void * FUN_002cb660(int arg0) {
    FUN_002cb7c0();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5868C8), (igMemoryPoolView *)arg0));
}

igMetaObject *igContextExtInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igContextExtInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cb7c0();
    return g_igContextExtInfo_metaObject[0];
}

int igContextExtInfo_GetVTable(void) {
    igContextExtInfo info;
    int temp_s0;
    int *q0;
    igObject *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader((igObject *)&info);
    info._vtable = (int)&DAT_005318b0[0];
    q1 = (igObject *)&info._pMeta;
    *(int *)q1 = 0;
    q0 = &info._pName;
    *(int *)q0 = 0;
    temp_s0 = *(int *)((char *)&info + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    info._vtable = (int)&DAT_005318b0[0];
    if (q0 != 0) {
        temp_v1 = *(int **)q0;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(igObject **)q1;
        if (q1 != 0) {
            q1->_refCount = (int)((int) (q1->_refCount - 1));
            if (((unsigned long long) ((long long)(int) q1->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s0;
}

void FUN_002cb7c0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igContextExtInfo_Register);
}

void igContextExtInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igContextExtInfo_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igContextExtInfo_GetMetaObject,
        igContextExtInfo_className,
        0x14, /* instance size */
        igContextExtInfo_GetVTable,
        &igContextExtInfo_InitFields,
        0, /* extra callback item */
        g_igContextExtInfo_callbackList /* callback list */
    );
}

void thunk_igContextExtInfo_GetMetaObject(void) {
    igContextExtInfo_GetMetaObject();
}

void igContextExtInfo_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igContextExtInfo_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igContextExtInfo_ctorTable[0], 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_002be610();
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    igStringMetaField_SetDefaultText((int *)temp_v0, 0);
    *(char *)((char *)(temp_v0) + 53) = 1;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    *(int *)((char *)(temp_s1_2) + 60) = FUN_002cc2c0();
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igContextExtInfo_fieldTable[0], (igMetaField ***)&DAT_004c1440[0], &DAT_004c1450[0], temp_s2);
}

