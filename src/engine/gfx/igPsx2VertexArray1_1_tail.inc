igMetaObject *FUN_00152370(void) {
    if (g_igPsx2VertexArray1_1_metaObject == 0) {
        g_igPsx2VertexArray1_1_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igPsx2VertexArray1_1_metaObject;
}

igMetaObject *igPsx2VertexArray1_1_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2VertexArray1_1_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001525e0();
    return g_igPsx2VertexArray1_1_metaObject;
}

int igPsx2VertexArray1_1_GetVTable(void) {
    struct Obj_152410 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w[5] = 0;
    obj.w[6] = 0;
    obj.vt = &g_igPsx2VertexArray1_1_vtable[0];
    obj.w[11] = 0;
    obj.w[12] = 0;
    obj.w[13] = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj.vt = &g_igPsx2VertexArray1_1_vtable[0];
    FUN_00152560((void **)&obj.w[13], -1);
    igSmartPointer_igPointerList_Destruct((igSmartPointer<igObject> *)&obj.w[12], -1);
    igSmartPointer_igPointerList_Destruct((igSmartPointer<igObject> *)&obj.w[11], -1);
    FUN_001524c0((S_1524c0 *)&obj, 0);
    return t;
}

void *FUN_001524c0(struct S_1524c0 *arg0, short arg1) {
    void *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_00526480[0];
        if (&arg0->f18) {
            p = arg0->f18;
            if (p != 0) {
                rc = *(int *)((char *)(p) + 4) - 1;
                *(int *)((char *)(p) + 4) = rc;
                if (((unsigned long long) ((long long) *(int *)((char *)(p) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((igObject *)p);
                }
            }
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

void **FUN_00152560(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)((void *)(*arg0));
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void FUN_001525e0(void)
{
    igMetaObject_RunStaticInit(igPsx2VertexArray1_1_Register);
}

static igMetaObjectCallback g_igPsx2VertexArray1_1_callbackList[] = { igPointerList_EnsureRegistered, FUN_001528e0, 0 };

CallbackArray *igPsx2VertexArray1_1_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2VertexArray1_1_metaObject,
        igVertexArray1_1_Register,
        igVertexArray1_1_GetPublishedMetaObject,
        thunk_igPsx2VertexArray1_1_GetMetaObject,
        "igPsx2VertexArray1_1",
        0x90, /* instance size */
        igPsx2VertexArray1_1_GetVTable,
        &igPsx2VertexArray1_1_InitFields,
        0, /* extra callback item */
        g_igPsx2VertexArray1_1_callbackList /* callback list */
    );
}

igMetaObject *FUN_00152670(void) {
    return g_igVertexArray1_1_metaObject;
}

static FieldFactory g_igPsx2VertexArray1_1_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igIntArrayMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igPsx2VertexArray1_1_fieldTable[] = {
    "_pBlendedVertsList",
    "_pBlendedNormsList",
    "_pWaitSeqList",
    "_lastArrayUsed",
    "_lSequence",
    "_textureCoordCompiled",
    "_multipassCompiled",
};
static igMetaField **g_igPsx2VertexArray1_1_fieldHandles[] = {
    &g_igPsx2VertexArray1_1_pBlendedVertsListMetaField,
    &g_igPsx2VertexArray1_1_pBlendedNormsListMetaField,
    &g_igPsx2VertexArray1_1_pWaitSeqListMetaField,
    &g_igPsx2VertexArray1_1_lastArrayUsedMetaField,
    &g_igPsx2VertexArray1_1_lSequenceMetaField,
    &g_igPsx2VertexArray1_1_textureCoordCompiledMetaField,
    &g_igPsx2VertexArray1_1_multipassCompiledMetaField,
};
static int g_igPsx2VertexArray1_1_fieldOffsets[] = {
    48,
    52,
    56,
    60,
    64,
    72,
    136,
};

void igPsx2VertexArray1_1_InitFields(void) {
    void *f5;
    void *f1;
    void *f2;
    int fieldStart;
    void *f4;
    void *f3;
    igMetaObject *meta;

    meta = g_igPsx2VertexArray1_1_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igPsx2VertexArray1_1_ctorTable, 7);
    f1 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((igObjectRefMetaField *)f1)->_metaObject = igPointerList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)f1)->_persistent = 0;
    f2 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 1));
    ((igObjectRefMetaField *)f2)->_metaObject = igPointerList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)f2)->_persistent = 0;
    f3 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 2));
    ((igObjectRefMetaField *)f3)->_metaObject = FUN_00152800();
    ((igObjectRefMetaField *)f3)->_persistent = 0;
    f4 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 3));
    igIntMetaField_SetDefault((igMetaField *)f4, -1);
    ((igIntMetaField *)f4)->_persistent = 0;
    ((igLongMetaField *)(igMetaObject_GetFieldAt(meta, fieldStart + 4)))->_persistent = 0;
    f5 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 5));
    ((igIntArrayMetaField *)f5)->_num = 0x10;
    ((igIntArrayMetaField *)f5)->_persistent = 0;
    ((igIntMetaField *)(igMetaObject_GetFieldAt(meta, fieldStart + 6)))->_persistent = 0;
    igMetaObject_NameFields(meta, g_igPsx2VertexArray1_1_fieldTable, g_igPsx2VertexArray1_1_fieldHandles, g_igPsx2VertexArray1_1_fieldOffsets, fieldStart);
    ((igMetaObject *)(g_igPsx2VertexArray1_1_metaObject))->_writeProxy = (int)(&thunk_igVertexArray1_1_GetMetaObject);
}

int FUN_001527c0(int arg0) {
    FUN_001528e0();
    return (int)igMetaObject_CreateInstance(g_igPsx2LongList_metaObject, (igMemoryPoolView *)arg0);
}

int FUN_00152800(void) {
    if (g_igPsx2LongList_metaObject == 0) {
        g_igPsx2LongList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return (int)g_igPsx2LongList_metaObject;
}

