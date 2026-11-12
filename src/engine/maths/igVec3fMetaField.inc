void FUN_00187890(int arg0) {
    FUN_001879b0();
    igMetaObject_CreateInstance(*(int *)0x560F70, arg0);
}

igMetaObject *igVec3fMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igVec3fMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001879b0();
    return g_igVec3fMetaField_metaObject[0];
}

int igVec3fMetaField_GetVTable(void) {
    struct Obj5 obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igMetaField_Init(&obj);
    obj.vt = &DAT_005274e0[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052f230[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void FUN_001879b0(void)
{
    igMetaObject_RunStaticInit(igVec3fMetaField_Register);
}

void igVec3fMetaField_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVec3fMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igVec3fMetaField_GetMetaObject,
        igVec3fMetaField_className,
        0x34, /* instance size */
        igVec3fMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igVec3fMetaField_callbackList /* callback list */
    );
}

void thunk_igVec3fMetaField_GetMetaObject(void) {
    igVec3fMetaField_GetMetaObject();
}

void FUN_00187a40(void) {
    void *temp_s0;

    if (DAT_00560f78[0] == 0) {
        DAT_00560f78[0] = (int)(igMetaObject_CreateInstance(DAT_00560f70[0], Memory_GetAllocatorBySelector(DAT_00587040[0])));
        temp_s0 = (void *)(DAT_00560f78[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            {
                void *held = (void *)DAT_00560f78[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_00560f78[0]) + 18) = (short) (*(int *)((char *)(FUN_002fc250()) + 12) - 1);
            igMetaField_FinalizeDescriptor(DAT_00560f78[0]);
        }
    }
}

int FUN_00187b10(void) {
    if (DAT_00560f78[0] == 0) {
        FUN_001879b0();
    }
    return DAT_00560f78[0];
}

