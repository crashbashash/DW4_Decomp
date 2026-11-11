igMetaObject *igDoubleArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igDoubleArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c6f40();
    return g_igDoubleArrayMetaField_metaObject[0];
}

int igDoubleArrayMetaField_GetVTable(void) {
    struct F_2c6eb0 o;
    int r;
    int *s;
    int *h;
    int c;
    igMetaField_Init((igMetaField *)&o);
    o.vt = DAT_00530790;
    r = *(int *)((char *)&o + *(int *)(((char * *)DAT_00586dc8)[0] + 916));
    o.vt = DAT_0052f230;
    if (&o.str != 0) {
        s = o.str;
        if (s != 0) {
            h = s - 2;
            c = s[-1] - 1;
            s[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader((StringChunkOwnerView *)(*h), (int)h);
        }
    }
    return r;
}

void FUN_002c6f40(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDoubleArrayMetaField_Register);
}

void igDoubleArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igDoubleArrayMetaField_metaObject),
        igDoubleMetaField_Register,
        igDoubleMetaField_GetPublishedMetaObject,
        thunk_igDoubleArrayMetaField_GetMetaObject,
        igDoubleArrayMetaField_className,
        0x38, /* instance size */
        igDoubleArrayMetaField_GetVTable,
        &igDoubleArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igDoubleArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igDoubleArrayMetaField_GetMetaObject(void) {
    igDoubleArrayMetaField_GetMetaObject();
}

int FUN_002c6fe0(void) {
    return DAT_00586638[0];
}

void igDoubleArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00586648[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004c10c8[0], 1);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004c10d0[0], (igMetaField ***)&DAT_004c10d8[0], &DAT_004c10e0[0], temp_s1);
}

void FUN_002c7080(void) {
    M_2c7080 *temp_s0;
    M_2c7080 *p;
    int len;

    if (DAT_00586650[0] == 0) {
        DAT_00586650[0] = ((M_2c7080 *)igMetaObject_CreateInstance((CreateMeta *)DAT_00586648[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(DAT_00587040[0])))));
        temp_s0 = DAT_00586650[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((R_2c7080 *)FUN_002fc250())), (RefHeader *)temp_s0);
            p = DAT_00586650[0];
            p->f4 = p->f4 - 1;
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
            len = ((R_2c7080 *)FUN_002fc250())->f12;
            DAT_00586650[0]->f18 = len - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00586650[0]);
        }
    }
}

