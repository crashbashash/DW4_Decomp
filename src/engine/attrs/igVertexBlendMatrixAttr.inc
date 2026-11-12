void FUN_00130c10(int arg0) {
    FUN_00130cf0();
    igMetaObject_CreateInstance(*(int *)0x55EC68, arg0);
}

igMetaObject *igVertexBlendMatrixAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexBlendMatrixAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00130cf0();
    return g_igVertexBlendMatrixAttr_metaObject[0];
}

int igVertexBlendMatrixAttr_GetVTable(void) {
    union U_130ca0 u;
    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_005226c0[0]);
    igMatrix44f_SetIdentity(&u.w[3]);
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}

void FUN_00130cf0(void)
{
    igMetaObject_RunStaticInit(igVertexBlendMatrixAttr_Register);
}

void igVertexBlendMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVertexBlendMatrixAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igVertexBlendMatrixAttr_GetMetaObject,
        igVertexBlendMatrixAttr_className,
        0x50, /* instance size */
        igVertexBlendMatrixAttr_GetVTable,
        &igVertexBlendMatrixAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igVertexBlendMatrixAttr_GetMetaObject(void) {
    igVertexBlendMatrixAttr_GetMetaObject();
}

void igVertexBlendMatrixAttr_InitFields(void) {
    int tf;
    int temp_s2;
    int temp_s1;
    void *temp_s0;
    struct M o1;
    struct V o2;
    struct V o3;
    struct V o4;
    struct V o5;

    temp_s0 = (void *)DAT_0055ec68[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485a70[0], 2);
    temp_s1 = (int)igMetaObject_GetFieldAt(temp_s0, temp_s2);
    o5.x = 0;
    o5.y = 0;
    o5.z = 0;
    o5.w = 0x3F800000;
    o4.x = 0;
    o4.y = 0;
    o4.z = 0x3F800000;
    o4.w = 0;
    o3.x = 0;
    o3.y = 0x3F800000;
    o3.z = 0;
    o3.w = 0;
    o2.x = 0x3F800000;
    o2.y = 0;
    o2.z = 0;
    o2.w = 0;
    FUN_00130e90(&o1, &o2, &o3, &o4, &o5);
    FUN_0018c640(temp_s1, &o1);
    tf = (int)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1);
    *(int *)((char *)tf + 48) = (int)&FUN_00141900;
    igMetaObject_NameFields(temp_s0, &DAT_00485a78[0], &DAT_00485a80[0], &DAT_00485a88[0], temp_s2);
}

void FUN_00130e90(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4) {
    *(float *)((char *)(arg0) + 0) = (float) *(float *)((char *)(arg1) + 0);
    *(float *)((char *)(arg0) + 4) = (float) *(float *)((char *)(arg1) + 4);
    *(float *)((char *)(arg0) + 8) = (float) *(float *)((char *)(arg1) + 8);
    *(float *)((char *)(arg0) + 12) = (float) *(float *)((char *)(arg1) + 12);
    *(float *)((char *)(arg0) + 16) = (float) *(float *)((char *)(arg2) + 0);
    *(float *)((char *)(arg0) + 20) = (float) *(float *)((char *)(arg2) + 4);
    *(float *)((char *)(arg0) + 24) = (float) *(float *)((char *)(arg2) + 8);
    *(float *)((char *)(arg0) + 28) = (float) *(float *)((char *)(arg2) + 12);
    *(float *)((char *)(arg0) + 32) = (float) *(float *)((char *)(arg3) + 0);
    *(float *)((char *)(arg0) + 36) = (float) *(float *)((char *)(arg3) + 4);
    *(float *)((char *)(arg0) + 40) = (float) *(float *)((char *)(arg3) + 8);
    *(float *)((char *)(arg0) + 44) = (float) *(float *)((char *)(arg3) + 12);
    *(float *)((char *)(arg0) + 48) = (float) *(float *)((char *)(arg4) + 0);
    *(float *)((char *)(arg0) + 52) = (float) *(float *)((char *)(arg4) + 4);
    *(float *)((char *)(arg0) + 56) = (float) *(float *)((char *)(arg4) + 8);
    *(float *)((char *)(arg0) + 60) = (float) *(float *)((char *)(arg4) + 12);
}

