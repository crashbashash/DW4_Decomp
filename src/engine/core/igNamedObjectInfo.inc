igMetaObject *igNamedObjectInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igNamedObjectInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bdfc0();
    return g_igNamedObjectInfo_metaObject[0];
}

int igNamedObjectInfo_GetVTable(void) {
    union U_2bdee0 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader((ObjectHeader *)u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_0052f150[0];
    q0 = (S_ref *)&u.b[20];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(((void * *)g_objectSystem)[0]) + 916)];
    u.vt = (int)&DAT_0052f150[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&DAT_00524950[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_002bdfc0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igNamedObjectInfo_Register);
}

void igNamedObjectInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igNamedObjectInfo_metaObject),
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igNamedObjectInfo_GetMetaObject,
        igNamedObjectInfo_className,
        0x18, /* instance size */
        igNamedObjectInfo_GetVTable,
        &igNamedObjectInfo_InitFields,
        0, /* extra callback item */
        g_igNamedObjectInfo_callbackList /* callback list */
    );
}

void thunk_igNamedObjectInfo_GetMetaObject(void) {
    igNamedObjectInfo_GetMetaObject();
}

void igNamedObjectInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igNamedObjectInfo_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004bfbb0[0], 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_002be100();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004bfbb8[0], (igMetaField ***)&DAT_004bfbc0[0], &DAT_004bfbc8[0], temp_s2);
}

