void beCriSndf_Create(int arg0) {
    FUN_003675b0();
    igMetaObject_CreateInstance(*(int *)0x589AB0, arg0);
}

igMetaObject *FUN_003674d0(void) {
    if (g_beCriSndf_metaObject[0] == 0) {
        g_beCriSndf_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beCriSndf_metaObject[0];
}

void *FUN_00367520(void) {
    igMetaObject *g = g_beCriSndf_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003675b0();
    }
    return g_beCriSndf_metaObject[0];
}

int beCriSndf_GetVTable(void) {
    int tmp[8];
    int off;

    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_00534dd0[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_003675b0(void)
{
    igMetaObject_RunStaticInit(beCriSndf_Register);
}

void *beCriSndf_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCriSndf_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCriSndf_GetMetaObject,
        beCriSndf_className,
        0x20, /* instance size */
        beCriSndf_GetVTable,
        beCriSndf_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beCriSndf_GetMetaObject(void)
{
    FUN_00367520();
}

void beCriSndf_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beCriSndf_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beCriSndf_ctorTable[0], 3);
    igMetaObject_NameFields(temp_s0, &g_beCriSndf_fieldTable[0], &DAT_004c7620[0], &DAT_004c7630[0], temp_s1);
}

