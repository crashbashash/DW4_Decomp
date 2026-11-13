int FUN_001a21b0(void) {
    if (DAT_00561b98[0] == 0) {
        DAT_00561b98[0] = igMetaEnum_Create(&PLAY_MODE[0], &DAT_0048c360[0], &DAT_0048c380[0], 5);
    }
    return DAT_00561b98[0];
}

igMetaObject *FUN_001a2210(void) {
    if (g_igEnbayaAnimationSource_metaObject[0] == 0) {
        g_igEnbayaAnimationSource_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igEnbayaAnimationSource_metaObject[0];
}

igMetaObject *igEnbayaAnimationSource_GetMetaObject(void)
{
    igMetaObject *g = g_igEnbayaAnimationSource_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a22f0();
    return g_igEnbayaAnimationSource_metaObject[0];
}

int igEnbayaAnimationSource_GetVTable(void) {
    union U_1a22b0 u;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_005291e0[0]);
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void FUN_001a22f0(void)
{
    igMetaObject_RunStaticInit(igEnbayaAnimationSource_Register);
}

void igEnbayaAnimationSource_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igEnbayaAnimationSource_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igEnbayaAnimationSource_GetMetaObject,
        igEnbayaAnimationSource_className,
        sizeof(igEnbayaAnimationSource),               /* Instance size. */
        igEnbayaAnimationSource_GetVTable,
        &igEnbayaAnimationSource_InitFields,
        FUN_001a24d0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igEnbayaAnimationSource_GetMetaObject(void) {
    igEnbayaAnimationSource_GetMetaObject();
}

void igEnbayaAnimationSource_InitFields(void) {
    igMemoryRefMetaField *temp_s2;
    igFloatMetaField *temp_v0;
    igLongMetaField *temp_v0_2;
    igUnsignedCharArrayMetaField *tf;
    igEnumMetaField *tf2;
    void *temp_s1;
    int temp_s0;
    temp_s1 = (void *)g_igEnbayaAnimationSource_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_igEnbayaAnimationSource_ctorTable[0], 6);
    temp_s2 = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0);
    temp_s2->_memType = FUN_002cc2c0();
    temp_s2->_destruct = 1;
    temp_s2->_releaseOnCopy = 1;
    temp_s2->_releaseOnReset = 1;
    tf = (igUnsignedCharArrayMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1);
    tf->_num = 3;
    FUN_0030e750(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2)), 3);
    tf2 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3);
    tf2->_getMetaEnumFunction = (int)FUN_001a21b0;
    temp_v0 = (igFloatMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4);
    FUN_002e3810(temp_v0, -1.0f);
    temp_v0->_persistent = 0;
    temp_v0_2 = (igLongMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5);
    FUN_002ebc00(temp_v0_2, -1);
    temp_v0_2->_persistent = 0;
    igMetaObject_NameFields(temp_s1, &g_igEnbayaAnimationSource_fieldTable[0], &DAT_0048c3e0[0], &DAT_0048c400[0], temp_s0);
    FUN_002fe480(FUN_001a24e0);
}

void FUN_001a24d0(void) {
    FUN_001c07d0();
}

void FUN_001a24e0(void) {
    FUN_001c07e0();
}

