igMetaObject *igUnsignedLongArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedLongArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b6b10();
    return g_igUnsignedLongArrayMetaField_metaObject[0];
}

int igUnsignedLongArrayMetaField_GetVTable(void) {
    struct Obj_2b6a80 obj;
    char *o;
    int *a1;
    int v0;
    int t;
    FUN_0030eb80((int **)&obj);
    obj.vt = &DAT_0052e330[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
    obj.vt = &DAT_0052f230[0];
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

void FUN_002b6b10(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedLongArrayMetaField_Register);
}

void igUnsignedLongArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedLongArrayMetaField_metaObject),
        igUnsignedLongMetaField_Register,
        igUnsignedLongMetaField_GetPublishedMetaObject,
        thunk_igUnsignedLongArrayMetaField_GetMetaObject,
        igUnsignedLongArrayMetaField_className,
        0x38, /* instance size */
        igUnsignedLongArrayMetaField_GetVTable,
        &igUnsignedLongArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igUnsignedLongArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igUnsignedLongArrayMetaField_GetMetaObject(void) {
    igUnsignedLongArrayMetaField_GetMetaObject();
}

int FUN_002b6bb0(void) {
    return DAT_00585710[0];
}

void igUnsignedLongArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00585720[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004bf2e8[0], 1);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004bf2f0[0], (igMetaField ***)&DAT_004bf2f8[0], &DAT_004bf300[0], temp_s1);
}

void FUN_002b6c50(void) {
    T_2b6c50 *temp_s0;
    T_2b6c50 *p;

    if (DAT_00585728[0] == 0) {
        DAT_00585728[0] = ((T_2b6c50 *)igMetaObject_CreateInstance((CreateMeta *)DAT_00585720[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(DAT_00587040[0])))));
        temp_s0 = DAT_00585728[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((C *)FUN_002fc250())), (RefHeader *)temp_s0);
            p = DAT_00585728[0];
            p->references = p->references - 1;
            if (((unsigned long long)(long long)p->references & 0x7fffffULL) == 0) {
                igObject_Destroy(p);
            }
            DAT_00585728[0]->s18 = ((C *)FUN_002fc250())->cnt - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00585728[0]);
        }
    }
}

