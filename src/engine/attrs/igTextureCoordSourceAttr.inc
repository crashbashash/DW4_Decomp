void FUN_001325a0(int arg0) {
    FUN_001326c0();
    igMetaObject_CreateInstance(*(int *)0x55ED68, arg0);
}

igMetaObject *FUN_001325e0(void) {
    if (g_igTextureCoordSourceAttr_metaObject[0] == 0) {
        g_igTextureCoordSourceAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igTextureCoordSourceAttr_metaObject[0];
}

igMetaObject *igTextureCoordSourceAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureCoordSourceAttr_metaObject[0] != 0) {
        ready = (g_igTextureCoordSourceAttr_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_001326c0();
done:
    return g_igTextureCoordSourceAttr_metaObject[0];
}

int igTextureCoordSourceAttr_GetVTable(void) {
    struct Obj_132680 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00522b40[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001326c0(void)
{
    igMetaObject_RunStaticInit(igTextureCoordSourceAttr_Register);
}

void igTextureCoordSourceAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureCoordSourceAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureCoordSourceAttr_GetMetaObject,
        igTextureCoordSourceAttr_className,
        0x18, /* instance size */
        igTextureCoordSourceAttr_GetVTable,
        &igTextureCoordSourceAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTextureCoordSourceAttr_GetMetaObject(void) {
    igTextureCoordSourceAttr_GetMetaObject();
}

void igTextureCoordSourceAttr_InitFields(void) {
    void *temp_v0_2;
    igMetaObject *temp_s0;
    int temp_s2;
    void *temp_v0;

    temp_s0 = g_igTextureCoordSourceAttr_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igTextureCoordSourceAttr_ctorTable[0], 3);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_00485ca0[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_001497a0);
    temp_v0_2 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2);
    *(int *)((char *)(temp_v0_2) + 48) = (int)(FUN_00140fd0);
    igMetaObject_NameFields(temp_s0, &g_igTextureCoordSourceAttr_fieldTable[0], &DAT_00485c80[0], &DAT_00485c90[0], temp_s2);
}

