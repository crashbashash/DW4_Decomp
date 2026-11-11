igMetaObject *igRawRefArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igRawRefArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bbec0();
    return g_igRawRefArrayMetaField_metaObject[0];
}

int igRawRefArrayMetaField_GetVTable(void) {
    struct F f;
    int temp_s0;
    int *temp_a1;
    int temp_v0;

    FUN_00305440((int **)&f);
    f.obj.vt = &DAT_0052ed50[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
    f.obj.vt = &DAT_0052f230[0];
    if (&f.ref != 0) {
        if (f.ref != 0) {
            temp_a1 = f.ref - 2;
            temp_v0 = f.ref[-1] - 1;
            f.ref[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_002bbec0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igRawRefArrayMetaField_Register);
}

void igRawRefArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igRawRefArrayMetaField_metaObject),
        igRawRefMetaField_Register,
        igRawRefMetaField_GetPublishedMetaObject,
        thunk_igRawRefArrayMetaField_GetMetaObject,
        igRawRefArrayMetaField_className,
        0x3C, /* instance size */
        igRawRefArrayMetaField_GetVTable,
        &igRawRefArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igRawRefArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igRawRefArrayMetaField_GetMetaObject(void) {
    igRawRefArrayMetaField_GetMetaObject();
}

int FUN_002bbf60(void) {
    return DAT_00585a80[0];
}

void igRawRefArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00585a90[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004bf990[0], 1);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004bf998[0], (igMetaField ***)&DAT_004bf9a0[0], &DAT_004bf9a8[0], temp_s1);
}

void FUN_002bc000(void) {
    Q *temp_s0;
    Q *p;

    if (DAT_00585a98[0] == 0) {
        DAT_00585a98[0] = ((Q *)igMetaObject_CreateInstance((CreateMeta *)DAT_00585a90[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(DAT_00587040[0])))));
        temp_s0 = DAT_00585a98[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((R_2bc000 *)FUN_002fc250())), (RefHeader *)temp_s0);
            p = DAT_00585a98[0];
            p->f4 -= 1;
            if ((p->f4 & 0x7fffff) == 0) {
                igObject_Destroy(p);
            }
            DAT_00585a98[0]->f18 = ((R_2bc000 *)FUN_002fc250())->f12 - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00585a98[0]);
        }
    }
}

