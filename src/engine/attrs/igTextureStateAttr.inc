void FUN_00131390(int arg0) {
    FUN_001314b0();
    igMetaObject_CreateInstance(*(int *)0x55ECA8, arg0);
}

int FUN_001313d0(void) {
    if (DAT_0055eca8[0] == 0) {
        DAT_0055eca8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055eca8[0];
}

igMetaObject *igTextureStateAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureStateAttr_metaObject[0] != 0) {
        ready = (g_igTextureStateAttr_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_001314b0();
done:
    return g_igTextureStateAttr_metaObject[0];
}

int igTextureStateAttr_GetVTable(void) {
    struct Obj_131470 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00522860[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001314b0(void)
{
    igMetaObject_RunStaticInit(igTextureStateAttr_Register);
}

void igTextureStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureStateAttr_GetMetaObject,
        igTextureStateAttr_className,
        0x14, /* instance size */
        igTextureStateAttr_GetVTable,
        &igTextureStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTextureStateAttr_GetMetaObject(void) {
    igTextureStateAttr_GetMetaObject();
}

void igTextureStateAttr_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;
    temp_s0 = (void *)DAT_0055eca8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485ad8[0], 2);
    temp_s1 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1);
    *(int *)((char *)temp_s1 + 48) = (int)FUN_00141710;
    igMetaObject_NameFields(temp_s0, &DAT_00485ae0[0], &DAT_00485ae8[0], &DAT_00485af0[0], temp_s2);
}

