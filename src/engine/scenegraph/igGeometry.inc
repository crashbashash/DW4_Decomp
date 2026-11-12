void FUN_0019faa0(int arg0) {
    FUN_0019fc00();
    igMetaObject_CreateInstance(*(int *)0x561A38, arg0);
}

igMetaObject *FUN_0019fae0(void) {
    if (g_igGeometry_metaObject[0] == 0) {
        g_igGeometry_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igGeometry_metaObject[0];
}

igMetaObject *igGeometry_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019fc00();
    return g_igGeometry_metaObject[0];
}

int igGeometry_GetVTable(void) {
    struct Obj_19fb80 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.vt = &DAT_00528e70[0];
    obj.w10 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00528e70[0];
    FUN_0019d0a0((void * *)&obj.w10, -1);
    FUN_0019c0e0((struct S_19c0e0 *)&obj, 0);
    return t;
}

void FUN_0019fc00(void)
{
    igMetaObject_RunStaticInit(igGeometry_Register);
}

void igGeometry_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igGeometry_metaObject),
        igAttrSet_Register,
        igAttrSet_GetPublishedMetaObject,
        thunk_igGeometry_GetMetaObject,
        igGeometry_className,
        0x2C, /* instance size */
        igGeometry_GetVTable,
        &igGeometry_InitFields_0019fca0[0],
        &igGeometry_PostInit_0019fdd0[0], /* extra callback item */
        g_igGeometry_callbackList /* callback list */
    );
}

void thunk_igGeometry_GetMetaObject(void) {
    igGeometry_GetMetaObject();
}

void FUN_0019fca0(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0_2;

    temp_s1 = (void *)(((void * *)g_igGeometry_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_0048c060[0], 1);
    temp_v0 = (void **)(((void * *)igMetaObject_FindFieldByName(temp_s1, &DAT_004e2710[0])));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_002d3890(temp_v0_2, 1);
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&DAT_00561a40[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    *(int *)((char *)(temp_v0_2) + 4) = (int)((int) (*(int *)((char *)(temp_v0_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_v0_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((void *)temp_v0_2);
    }
    temp_s0 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s2)));
    *(int *)((char *)(temp_s0) + 56) = FUN_00133e50();
    *(char *)((char *)(temp_s0) + 38) = 0;
    igMetaObject_NameFields(temp_s1, &DAT_0048c068[0], &DAT_0048c070[0], &DAT_0048c078[0], temp_s2);
}

void thunk_FUN_001c51d0(void) {
    FUN_001c51d0();
}

