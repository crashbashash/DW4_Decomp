int FUN_001a2c70(int arg0) {
    FUN_001a2d90();
    return igMetaObject_CreateInstance(*(int *)0x561CA8, arg0);
}

igMetaObject *igBlendListRecord_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendListRecord_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a2d90();
    return g_igBlendListRecord_metaObject[0];
}

int igBlendListRecord_GetVTable(void) {
    union U_1a2d00 u;
    void **q2;
    int temp_s0;
    void *temp_a0;

    igObject_InitHeader(u.b);
    q2 = &u.p[2];
    u.w[0] = (int)(&DAT_0052a670[0]);
    *q2 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_0052a670[0]);
    if (q2 != 0) {
        temp_a0 = *q2;
        if (temp_a0 != 0) {
            *(int *)((char *)(temp_a0) + 4) = (int)((int) (*(int *)((char *)(temp_a0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_a0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
    }
    return temp_s0;
}

void FUN_001a2d90(void)
{
    igMetaObject_RunStaticInit(igBlendListRecord_Register);
}

void igBlendListRecord_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igBlendListRecord_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igBlendListRecord_GetMetaObject,
        igBlendListRecord_className,
        0x10, /* instance size */
        igBlendListRecord_GetVTable,
        &igBlendListRecord_InitFields,
        0, /* extra callback item */
        g_igBlendListRecord_callbackList /* callback list */
    );
}

void thunk_igBlendListRecord_GetMetaObject(void) {
    igBlendListRecord_GetMetaObject();
}

void igBlendListRecord_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igBlendListRecord_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igBlendListRecord_ctorTable[0], 2);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001399d0();
    ((igMetaField *)temp_s1)->_persistent = 0;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0013b070();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    ((igMetaField *)temp_s1_2)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &g_igBlendListRecord_fieldTable[0], &DAT_0048c5c8[0], &DAT_0048c5d0[0], temp_s2);
}

