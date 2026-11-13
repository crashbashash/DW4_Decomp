igMetaObject *FUN_00131160(void) {
    if (g_igTextureUnloadAttr_metaObject[0] == 0) {
        g_igTextureUnloadAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igTextureUnloadAttr_metaObject[0];
}

igMetaObject *igTextureUnloadAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureUnloadAttr_metaObject[0] != 0) {
        ready = (g_igTextureUnloadAttr_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00131240();
done:
    return g_igTextureUnloadAttr_metaObject[0];
}

int igTextureUnloadAttr_GetVTable(void) {
    struct Obj_131200 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005227d0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00131240(void)
{
    igMetaObject_RunStaticInit(igTextureUnloadAttr_Register);
}

void igTextureUnloadAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureUnloadAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureUnloadAttr_GetMetaObject,
        igTextureUnloadAttr_className,
        0x14, /* instance size */
        igTextureUnloadAttr_GetVTable,
        &igTextureUnloadAttr_InitFields,
        0, /* extra callback item */
        g_igTextureUnloadAttr_callbackList /* callback list */
    );
}

void thunk_igTextureUnloadAttr_GetMetaObject(void) {
    igTextureUnloadAttr_GetMetaObject();
}

void igTextureUnloadAttr_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s3;
    void *temp_s0;

    temp_s0 = (void *)g_igTextureUnloadAttr_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igTextureUnloadAttr_ctorTable[0], 2);
    temp_s1 = igMetaObject_GetFieldAt(temp_s0, temp_s2);
    *(int *)((char *)temp_s1 + 56) = (int)FUN_00132ba0();
    *(char *)((char *)temp_s1 + 60) = 0;
    temp_s3 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1);
    *(int *)((char *)temp_s3 + 48) = (int)FUN_00141840;
    igMetaObject_NameFields(temp_s0, &g_igTextureUnloadAttr_fieldTable[0], &DAT_00485ac8[0], &DAT_00485ad0[0], temp_s2);
}

