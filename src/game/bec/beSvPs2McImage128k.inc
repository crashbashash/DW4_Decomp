void *FUN_00347c50(void) {
    igMetaObject *g = g_beSvPs2McImage128k_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00347ce0();
    }
    return g_beSvPs2McImage128k_metaObject[0];
}

int beSvPs2McImage128k_GetVTable(void) {
    struct Obj_347ca0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00538b60[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00347ce0(void)
{
    igMetaObject_RunStaticInit(beSvPs2McImage128k_Register);
}

void *beSvPs2McImage128k_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvPs2McImage128k_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSvPs2McImage128k_GetMetaObject,
        beSvPs2McImage128k_className,
        0x10, /* instance size */
        beSvPs2McImage128k_GetVTable,
        beSvPs2McImage128k_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvPs2McImage128k_GetMetaObject(void)
{
    FUN_00347c50();
}

void beSvPs2McImage128k_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSvPs2McImage128k_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3f08[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igMemoryRefMetaField *)temp_s1)->_memType = FUN_002cc2c0();
    igMetaObject_NameFields(temp_s0, &DAT_004c3f10[0], &DAT_004c3f18[0], &DAT_004c3f20[0], temp_s2);
}

