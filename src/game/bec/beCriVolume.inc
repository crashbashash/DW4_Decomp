igMetaObject *FUN_00366340(void) {
    if (g_beCriVolume_metaObject[0] == 0) {
        g_beCriVolume_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beCriVolume_metaObject[0];
}

igMetaObject *FUN_00366390(void) {
    igMetaObject *g = g_beCriVolume_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_00366420();
done:
    return g_beCriVolume_metaObject[0];
}

int beCriVolume_GetVTable(void) {
    struct Obj_3663e0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00535090[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00366420(void)
{
    igMetaObject_RunStaticInit(beCriVolume_Register);
}

void *beCriVolume_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCriVolume_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCriVolume_GetMetaObject,
        beCriVolume_className,
        0x20, /* instance size */
        beCriVolume_GetVTable,
        beCriVolume_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beCriVolume_GetMetaObject(void)
{
    FUN_00366390();
}

void beCriVolume_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beCriVolume_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7350[0], 6);
    igMetaObject_NameFields(temp_s0, &DAT_004c7370[0], &DAT_004c7390[0], &DAT_004c73b0[0], temp_s1);
}

