int FUN_002bc8d0(void) {
    if (DAT_00585ae8[0] == 0) {
        DAT_00585ae8[0] = ((int)igMetaEnum_Create((char *)&DAT_004f63a8[0], (char **)&DAT_004bfa38[0], &DAT_004bfa48[0], 3));
    }
    return DAT_00585ae8[0];
}

int FUN_002bc930(int arg0) {
    FUN_002bca90();
    return igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585AF0), (MemoryPool *)arg0);
}

igMetaObject *igPluginRepository_GetMetaObject(void)
{
    igMetaObject *g = g_igPluginRepository_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bca90();
    return g_igPluginRepository_metaObject[0];
}

int igPluginRepository_GetVTable(void) {
    union U_2bc9c0 u;
    int temp_s0;
    char *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader((ObjectHeader *)u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_00532de0[0];
    q0 = &u.b[12];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916)];
    u.vt = (int)&DAT_00532de0[0];
    if (q0 != 0) {
        temp_v1 = *(int **)q0;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
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

void FUN_002bca90(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPluginRepository_Register);
}

void igPluginRepository_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPluginRepository_metaObject),
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igPluginRepository_GetMetaObject,
        igPluginRepository_className,
        0x14, /* instance size */
        igPluginRepository_GetVTable,
        &igPluginRepository_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igPluginRepository_GetMetaObject(void) {
    igPluginRepository_GetMetaObject();
}

void igPluginRepository_InitFields(void) {
    igMetaObject *meta = DAT_00585af0[0];
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    igMetaObject_CreateFields(meta, (FieldFactory *)DAT_004bfa58, 2);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 1));
    *(int *)((char *)field + 52) = (int)FUN_002bc8d0;
    igMetaObject_NameFields(meta, (const char **)DAT_004bfa60, (igMetaField ***)DAT_004bfa68, (int *)DAT_004bfa70, base);
}

