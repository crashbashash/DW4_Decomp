void FUN_002cc300(int arg0) {
    FUN_002cc420();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586940), (MemoryPool *)arg0);
}

igMetaObject *igCharArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igCharArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cc420();
    return g_igCharArrayMetaField_metaObject[0];
}

int igCharArrayMetaField_GetVTable(void) {
    Obj_2cc390 o;
    int r;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    FUN_002d4da0((int **)&o);
    o.vt = &DAT_00530a80[0];
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
    o.vt = &DAT_0052f230[0];
    if (&o.str != 0) {
        temp_v1 = o.str;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return r;
}

void FUN_002cc420(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igCharArrayMetaField_Register);
}

void igCharArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igCharArrayMetaField_metaObject),
        igCharMetaField_Register,
        igCharMetaField_GetPublishedMetaObject,
        thunk_igCharArrayMetaField_GetMetaObject,
        igCharArrayMetaField_className,
        0x38, /* instance size */
        igCharArrayMetaField_GetVTable,
        &igCharArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igCharArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igCharArrayMetaField_GetMetaObject(void) {
    igCharArrayMetaField_GetMetaObject();
}

int FUN_002cc4c0(void) {
    return DAT_00586930[0];
}

void igCharArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00586940[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004c14f8[0], 1);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004c1500[0], (igMetaField ***)&DAT_004c1508[0], &DAT_004c1510[0], temp_s1);
}

void FUN_002cc560(void) {
    Q *temp_s0;
    Q *p;

    if (DAT_00586948[0] == 0) {
        DAT_00586948[0] = ((Q *)igMetaObject_CreateInstance((CreateMeta *)DAT_00586940[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(DAT_00587040[0])))));
        temp_s0 = DAT_00586948[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((R_2cc560 *)FUN_002fc250())), (RefHeader *)temp_s0);
            p = DAT_00586948[0];
            p->f4 -= 1;
            if ((p->f4 & 0x7fffff) == 0) {
                igObject_Destroy(p);
            }
            DAT_00586948[0]->f18 = ((R_2cc560 *)FUN_002fc250())->f12 - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00586948[0]);
        }
    }
}

