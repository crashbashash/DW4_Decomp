void FUN_002c63c0(int arg0) {
    FUN_002c64e0();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x5865B0), (MemoryPool *)arg0);
}

igMetaObject *igEnumArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igEnumArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c64e0();
    return g_igEnumArrayMetaField_metaObject[0];
}

int igEnumArrayMetaField_GetVTable(void) {
    union U_2c6450 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    FUN_002dc900((int **)u.b);
    u.vt = (int)&DAT_005304f0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(((void * *)g_objectSystem)[0]) + 916)];
    u.vt = (int)&g_igMetaField_vtable[0];
    ps = &u.b[12];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
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

void FUN_002c64e0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igEnumArrayMetaField_Register);
}

void igEnumArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igEnumArrayMetaField_metaObject),
        igEnumMetaField_Register,
        igEnumMetaField_GetPublishedMetaObject,
        thunk_igEnumArrayMetaField_GetMetaObject,
        igEnumArrayMetaField_className,
        0x3C, /* instance size */
        igEnumArrayMetaField_GetVTable,
        &igEnumArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igEnumArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igEnumArrayMetaField_GetMetaObject(void) {
    igEnumArrayMetaField_GetMetaObject();
}

igMetaObject *FUN_002c6580(void) {
    return g_igEnumMetaField_metaObject[0];
}

void igEnumArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igEnumArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004c0f98[0], 1);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004c0fa0[0], (igMetaField ***)&DAT_004c0fa8[0], &DAT_004c0fb0[0], temp_s1);
}

void FUN_002c6620(void) {
    int *s0;
    int *g;

    if (g_igEnumArrayMetaField_descriptor[0] == 0) {
        g_igEnumArrayMetaField_descriptor[0] = ((int *)igMetaObject_CreateInstance((CreateMeta *)g_igEnumArrayMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])))));
        s0 = g_igEnumArrayMetaField_descriptor[0];
        if (s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((int *)FUN_002fc250())), (RefHeader *)s0);
            g = g_igEnumArrayMetaField_descriptor[0];
            g[1] = g[1] - 1;
            if ((g[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(g);
            }
            *(short *)((char *)g_igEnumArrayMetaField_descriptor[0] + 18) = (short)(((int *)FUN_002fc250())[3] - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igEnumArrayMetaField_descriptor[0]);
        }
    }
}

