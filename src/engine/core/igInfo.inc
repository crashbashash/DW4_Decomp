igMetaObject *igInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c3690();
    return g_igInfo_metaObject[0];
}

int igInfo_GetVTable(void) {
    union U_2c3600 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;
    igObject_InitHeader((ObjectHeader *)u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_0052fde0[0];
    s0 = *(int *)&u.b[*(int *)((char *)(((void * *)g_objectSystem)[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*a1), (int)a1);
            }
        }
    }
    return s0;
}

void FUN_002c3690(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igInfo_Register);
}

void igInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igInfo_metaObject),
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igInfo_GetMetaObject,
        igInfo_className,
        0x14, /* instance size */
        igInfo_GetVTable,
        &igInfo_InitFields,
        0, /* extra callback item */
        g_igInfo_callbackList /* callback list */
    );
}

void thunk_igInfo_GetMetaObject(void) {
    igInfo_GetMetaObject();
}

void igInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igInfo_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004c0620[0], 2);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_002c7300();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    ((igMetaField *)temp_s1)->_persistent = 0;
    FUN_002d3890((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1))), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004c0628[0], (igMetaField ***)&DAT_004c0630[0], &DAT_004c0638[0], temp_s2);
}

