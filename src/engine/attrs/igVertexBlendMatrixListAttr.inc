void FUN_00130930(int arg0) {
    FUN_00130a70();
    igMetaObject_CreateInstance(*(int *)0x55EC28, arg0);
}

igMetaObject *igVertexBlendMatrixListAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexBlendMatrixListAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00130a70();
    return g_igVertexBlendMatrixListAttr_metaObject[0];
}

int igVertexBlendMatrixListAttr_GetVTable(void) {
    union U_1309c0 u;
    int temp_s0;
    S_ref *q0;
    int pi = (int)u.b;
    igObject_InitHeader(pi);
    u.vt = (int)&DAT_00522640[0];
    q0 = (S_ref *)&u.b[24];
    *(int *)q0 = 0;
    igMatrix44f_SetIdentity(&u.b[28]);
    igMatrix44f_SetIdentity(pi + 92);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00522630[4];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    return temp_s0;
}

void FUN_00130a70(void)
{
    igMetaObject_RunStaticInit(igVertexBlendMatrixListAttr_Register);
}

void igVertexBlendMatrixListAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVertexBlendMatrixListAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igVertexBlendMatrixListAttr_GetMetaObject,
        igVertexBlendMatrixListAttr_className,
        0x9C, /* instance size */
        igVertexBlendMatrixListAttr_GetVTable,
        &igVertexBlendMatrixListAttr_InitFields,
        0, /* extra callback item */
        g_igVertexBlendMatrixListAttr_callbackList /* callback list */
    );
}

void thunk_igVertexBlendMatrixListAttr_GetMetaObject(void) {
    igVertexBlendMatrixListAttr_GetMetaObject();
}

void igVertexBlendMatrixListAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0_2;
    void *temp_v0;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055ec28[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004859f0[0], 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001e4ae0();
    ((igObjectRefMetaField *)temp_s1)->_construct = 1;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igMetaField *)temp_v0)->_persistent = 0;
    ((igMetaField *)temp_v0)->_isAlikeShallowMethod = 3;
    ((igMetaField *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4)))->_persistent = 0;
    ((igMetaField *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5)))->_persistent = 0;
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    FUN_002ea4b0(temp_v0_2, -1);
    ((igMetaField *)temp_v0_2)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00485a10[0], &DAT_00485a30[0], &DAT_00485a50[0], temp_s2);
}

