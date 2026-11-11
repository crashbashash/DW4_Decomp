void **igMetaObject_Create(int allocator) {
    void **metaObject;

    if (*g_objectSystem[0] != 0) {
        igMetaObject_EnsureRegistered();
        metaObject = (void **)(((void **)igMetaObject_CreateInstance((CreateMeta *)(((int *)g_igMetaObject_metaObject)[0]), (MemoryPool *)allocator)));
    } else {
        metaObject = (void **)(((void **)igObject_AllocateRawStorage(0x64, 0, (void **)allocator)));
        if (metaObject != 0) {
            metaObject = (void **)(((void **)igMetaObject_Construct((igMetaObject *)metaObject, 1)));
        }
        ((igObjectSlot09 *)(metaObject))->vfunc_09();
        ((igObjectSlot07 *)(metaObject))->vfunc_07((int)(0));
    }
    return metaObject;
}

void *Gap__Core__igMetaObject__vfunc_21(int arg0, int arg1) {
    void *r;
    if (*DAT_00586dc8[0] != 0) {
        igMetaObject_EnsureRegistered();
        r = ((void *)igObject_CloneViaMetadata((void **)arg0, arg1));
    } else {
        r = igObject_AllocateRawStorageDefault(0x64, 0);
        if (r != 0) {
            r = igMetaObject_CopyConstruct((igMetaObject *)r, (void *)arg0);
        }
    }
    return r;
}

int FUN_002be610(void) {
    if (DAT_00585be8[0] == 0) {
        DAT_00585be8[0] = ((int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))));
    }
    return DAT_00585be8[0];
}

igMetaObject *igMetaObject_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaObject_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMetaObject_EnsureRegistered();
    return g_igMetaObject_metaObject[0];
}

int igMetaObject_GetVTable(void) {
    union U_2be6b0 u;
    int *temp_a1;
    int *temp_a1_2;
    int temp_s0;
    int temp_v0;
    int temp_v0_2;
    void *temp_v1;
    void *temp_v1_2;

    igMetaObject_Init((igMetaObject *)u.b);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916)];
    u.w[0] = (int)(&DAT_00532bb0[0]);
    if (&u.p[24] != 0) {
        temp_v1 = (void *)(u.p[24]);
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    if (&u.p[7] != 0) {
        temp_v1_2 = (void *)(u.p[7]);
        if (temp_v1_2 != 0) {
            temp_a1_2 = (int *)((char *)temp_v1_2 - 8);
            temp_v0_2 = *(int *)((char *)(temp_v1_2) - 4) - 1;
            *(int *)((char *)(temp_v1_2) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1_2), (int)temp_a1_2);
            }
        }
    }
    return temp_s0;
}

void igMetaObject_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMetaObject_Register);
}

void igMetaObject_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMetaObject_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMetaObject_GetMetaObject,
        igMetaObject_className,
        0x64, /* instance size */
        igMetaObject_GetVTable,
        &igMetaObject_InitFields,
        0, /* extra callback item */
        g_igMetaObject_callbackList /* callback list */
    );
}

void thunk_igMetaObject_GetMetaObject(void) {
    igMetaObject_GetMetaObject();
}

void igMetaObject_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_s1;

    temp_s1 = (void *)DAT_00585be8[0];
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, (igMetaField * (**)(void *))&DAT_004bfc10[0], 0x19);
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0)));
    FUN_002ea4b0((void **)temp_v0, -1);
    ((igMetaField *)temp_v0)->_persistent = 0;
    temp_v0_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1)));
    FUN_002ea4b0((void **)temp_v0_2, -1);
    ((igMetaField *)temp_v0_2)->_persistent = 0;
    FUN_002ea4b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2))), 1);
    FUN_002d3890((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5))), 1);
    igStringMetaField_SetDefaultText((int *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 7))), 0);
    temp_v0_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 8)));
    FUN_002ea4b0((void **)temp_v0_3, -1);
    ((igMetaField *)temp_v0_3)->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 9))))->_persistent = 0;
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xA)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_002c2790();
    ((igObjectRefMetaField *)temp_s2)->_construct = 1;
    ((igObjectRefMetaField *)temp_s2)->_destruct = 1;
    ((igObjectRefMetaField *)temp_s2)->_refCounted = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xB))))->_persistent = 0;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xC)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_002c2ae0();
    ((igObjectRefMetaField *)temp_s2_2)->_destruct = 1;
    ((igObjectRefMetaField *)temp_s2_2)->_refCounted = 0;
    ((igObjectRefMetaField *)temp_s2_2)->_persistent = 0;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xD)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_002c2ae0();
    ((igObjectRefMetaField *)temp_s2_3)->_destruct = 1;
    ((igObjectRefMetaField *)temp_s2_3)->_refCounted = 0;
    ((igObjectRefMetaField *)temp_s2_3)->_persistent = 0;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xE)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_002be610();
    ((igObjectRefMetaField *)temp_s2_4)->_refCounted = 0;
    ((igObjectRefMetaField *)temp_s2_4)->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xF))))->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0x10))))->_persistent = 0;
    temp_v0_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0x11)));
    ((igObjectRefMetaField *)temp_v0_4)->_metaObject = (int)((int) DAT_00587198[0]);
    ((igObjectRefMetaField *)temp_v0_4)->_destruct = 1;
    ((igObjectRefMetaField *)temp_v0_4)->_refCounted = 0;
    ((igObjectRefMetaField *)temp_v0_4)->_persistent = 0;
    temp_v0_5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0x12)));
    FUN_002ea4b0((void **)temp_v0_5, -1);
    ((igMetaField *)temp_v0_5)->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0x13))))->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0x14))))->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0x15))))->_persistent = 0;
    temp_v0_6 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0x16)));
    FUN_0030eda0((void **)temp_v0_6, 4);
    ((igMetaField *)temp_v0_6)->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0x17))))->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, (const char **)&DAT_004bfc80[0], (igMetaField ***)&DAT_004bfcf0[0], &DAT_004bfd60[0], temp_s0);
}

void FUN_002bea90(int arg0) {
    FUN_002bebb0();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585CB8), (MemoryPool *)arg0);
}

