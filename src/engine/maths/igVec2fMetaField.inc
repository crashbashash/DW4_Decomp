void FUN_00187b50(int arg0) {
    FUN_00187c70();
    igMetaObject_CreateInstance(*(int *)0x560F88, arg0);
}

igMetaObject *igVec2fMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igVec2fMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00187c70();
    return g_igVec2fMetaField_metaObject[0];
}

int igVec2fMetaField_GetVTable(void) {
    Obj6 o;
    int r;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    igMetaField_Init(&o);
    o.vt = &DAT_005275e0[0];
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0052f230[0];
    if (&o.str != 0) {
        temp_v1 = o.str;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return r;
}

void FUN_00187c70(void)
{
    igMetaObject_RunStaticInit(igVec2fMetaField_Register);
}

void igVec2fMetaField_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVec2fMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igVec2fMetaField_GetMetaObject,
        igVec2fMetaField_className,
        0x34, /* instance size */
        igVec2fMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igVec2fMetaField_callbackList /* callback list */
    );
}

void thunk_igVec2fMetaField_GetMetaObject(void) {
    igVec2fMetaField_GetMetaObject();
}

void FUN_00187d00(void) {
    void *temp_s0;

    if (DAT_00560f90[0] == 0) {
        DAT_00560f90[0] = (int)(igMetaObject_CreateInstance(DAT_00560f88[0], Memory_GetAllocatorBySelector(DAT_00587040[0])));
        temp_s0 = (void *)(DAT_00560f90[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            {
                void *held = (void *)DAT_00560f90[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_00560f90[0]) + 18) = (short) (*(int *)((char *)(FUN_002fc250()) + 12) - 1);
            igMetaField_FinalizeDescriptor(DAT_00560f90[0]);
        }
    }
}

int FUN_00187dd0(void) {
    if (DAT_00560f90[0] == 0) {
        FUN_00187c70();
    }
    return DAT_00560f90[0];
}

