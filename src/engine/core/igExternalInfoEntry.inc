void FUN_002c4f80(int arg0) {
    FUN_002c50a0();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x5863F8), (MemoryPool *)arg0);
}

igMetaObject *igExternalInfoEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igExternalInfoEntry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c50a0();
    return g_igExternalInfoEntry_metaObject[0];
}

int igExternalInfoEntry_GetVTable(void) {
    union U_2c5010 u;
    int temp_s0;
    int *p;
    int *q;

    igObject_InitHeader((ObjectHeader *)u.b);
    *(int *)&u.b[8] = 0;
    u.vt = (int)&DAT_00530200[0];
    p = (int *)&u.b[28];
    q = (int *)&u.b[36];
    *p = 0;
    *q = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(((void * *)g_objectSystem)[0]) + 916)];
    u.vt = (int)&DAT_00530200[0];
    FUN_00130720(q, -1);
    FUN_00130720(p, -1);
    FUN_0014f4e0(u.b, 0);
    return temp_s0;
}

void FUN_002c50a0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igExternalInfoEntry_Register);
}

void igExternalInfoEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igExternalInfoEntry_metaObject),
        igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        thunk_igExternalInfoEntry_GetMetaObject,
        igExternalInfoEntry_className,
        0x28, /* instance size */
        igExternalInfoEntry_GetVTable,
        &igExternalInfoEntry_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igExternalInfoEntry_GetMetaObject(void) {
    igExternalInfoEntry_GetMetaObject();
}

void igExternalInfoEntry_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igExternalInfoEntry_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004c0c00[0], 3);
    igStringMetaField_SetDefaultText((int *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 0);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1)), -1);
    igStringMetaField_SetDefaultText((int *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2)), 0);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004c0c10[0], (igMetaField ***)&DAT_004c0c20[0], &DAT_004c0c30[0], temp_s1);
}

