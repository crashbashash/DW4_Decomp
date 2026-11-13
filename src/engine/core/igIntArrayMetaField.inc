void FUN_002c30d0(int arg0) {
    FUN_002c31f0();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586108), (MemoryPool *)arg0);
}

igMetaObject *igIntArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igIntArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c31f0();
    return g_igIntArrayMetaField_metaObject[0];
}

int igIntArrayMetaField_GetVTable(void) {
    struct Obj_2c3160 obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igIntMetaField_Init((igMetaField *)&obj);
    obj.vt = &DAT_0052fce0[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    obj.vt = &g_igMetaField_vtable[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*a1), (int)a1);
            }
        }
    }
    return t;
}

void FUN_002c31f0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igIntArrayMetaField_Register);
}

void igIntArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igIntArrayMetaField_metaObject),
        igIntMetaField_Register,
        igIntMetaField_GetPublishedMetaObject,
        thunk_igIntArrayMetaField_GetMetaObject,
        igIntArrayMetaField_className,
        0x38, /* instance size */
        igIntArrayMetaField_GetVTable,
        &igIntArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igIntArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igIntArrayMetaField_GetMetaObject(void) {
    igIntArrayMetaField_GetMetaObject();
}

igMetaObject *FUN_002c3290(void) {
    return g_igIntMetaField_metaObject[0];
}

void igIntArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igIntArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igIntArrayMetaField_ctorTable[0], 1);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igIntArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004c0600[0], &DAT_004c0608[0], temp_s1);
}

void FUN_002c3330(void) {
    struct R *temp_s0;
    struct R *g;

    if (DAT_00586110[0] == 0) {
        DAT_00586110[0] = (R *)(((void *)igMetaObject_CreateInstance((CreateMeta *)g_igIntArrayMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(g_memoryContextMetaData))))));
        temp_s0 = DAT_00586110[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((struct M *)FUN_002fc250())), (RefHeader *)temp_s0);
            g = DAT_00586110[0];
            g->rc = g->rc - 1;
            if ((g->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(g);
            }
            DAT_00586110[0]->s18 = ((struct M *)FUN_002fc250())->f12 - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00586110[0]);
        }
    }
}

