void FUN_00188660(int arg0) {
    FUN_00188780();
    igMetaObject_CreateInstance(DAT_00561000[0], arg0);
}

igMetaObject *igMatrix44fMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrix44fMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00188780();
    return g_igMatrix44fMetaField_metaObject[0];
}

int igMatrix44fMetaField_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igMetaField_Init(u.b);
    u.vt = (int)&DAT_005276e0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0052f230[0];
    ps = &u.b[12];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_00188780(void)
{
    igMetaObject_RunStaticInit(igMatrix44fMetaField_Register);
}

void igMatrix44fMetaField_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMatrix44fMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igMatrix44fMetaField_GetMetaObject,
        igMatrix44fMetaField_className,
        0x34, /* instance size */
        igMatrix44fMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igMatrix44fMetaField_callbackList /* callback list */
    );
}

void thunk_igMatrix44fMetaField_GetMetaObject(void) {
    igMatrix44fMetaField_GetMetaObject();
}

void FUN_00188810(void) {
    void *temp_s0;

    if (DAT_00561008[0] == 0) {
        DAT_00561008[0] = (int)(igMetaObject_CreateInstance(DAT_00561000[0], Memory_GetAllocatorBySelector(DAT_00587040[0])));
        temp_s0 = (void *)(DAT_00561008[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            {
                void *held = (void *)DAT_00561008[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_00561008[0]) + 18) = (short) (*(int *)((char *)(FUN_002fc250()) + 12) - 1);
            igMetaField_FinalizeDescriptor(DAT_00561008[0]);
        }
    }
}

int FUN_001888e0(void) {
    if (DAT_00561008[0] == 0) {
        FUN_00188780();
    }
    return DAT_00561008[0];
}

