int FUN_00198cc0(int arg0) {
    FUN_00198e30();
    return igMetaObject_CreateInstance(*(int *)0x561500, arg0);
}

igMetaObject *igShaderInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igShaderInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00198e30();
    return g_igShaderInfo_metaObject[0];
}

int igShaderInfo_GetVTable(void) {
    union U_198d50 u;
    int temp_s1;
    void **q2;
    S_ref *q5;

    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    q2 = &u.p[2];
    *q2 = 0;
    u.w[0] = (int)(&DAT_00528790[0]);
    q5 = (S_ref *)&u.p[5];
    *(int *)q5 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00528790[0]);
    if (q5 != 0) {
        q5 = *(S_ref **)q5;
        if (q5 != 0) {
            q5->f4 = (int)((int) (q5->f4 - 1));
            if (((unsigned long long) ((long long) q5->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q5);
            }
        }
    }
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    if (q2 != 0) {
        temp_v1 = *q2;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s1;
}

void FUN_00198e30(void)
{
    igMetaObject_RunStaticInit(igShaderInfo_Register);
}

void igShaderInfo_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igShaderInfo_metaObject),
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igShaderInfo_GetMetaObject,
        igShaderInfo_className,
        0x18, /* instance size */
        igShaderInfo_GetVTable,
        &igShaderInfo_InitFields,
        thunk_FUN_001d8ab0, /* extra callback item */
        g_igShaderInfo_callbackList /* callback list */
    );
}

void thunk_igShaderInfo_GetMetaObject(void) {
    igShaderInfo_GetMetaObject();
}

void igShaderInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igShaderInfo_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igShaderInfo_ctorTable[0], 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_00198fa0();
    *(char *)((char *)(temp_s1) + 52) = 1;
    igMetaObject_NameFields(temp_s0, &g_igShaderInfo_fieldTable[0], &DAT_0048b630[0], &DAT_0048b638[0], temp_s2);
    FUN_002fe480((int)thunk_FUN_001d8b90);
}

void thunk_FUN_001d8ab0(void) {
    FUN_001d8ab0();
}

void thunk_FUN_001d8b90(void) {
    FUN_001d8b90();
}

