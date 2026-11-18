int FUN_001a5a70(int arg0) {
    FUN_001a5b90();
    return (int)igMetaObject_CreateInstance((igMetaObject *)g_igAttrStack_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *g_igAttrStack_metaObject;
igMetaField *g_igAttrStack_defaultMetaField;
igMetaField *g_igAttrStack_cachedOverrideMetaField;
igMetaField *g_igAttrStack_popProcMetaField;
igMetaField *g_igAttrStack_hasChangedFromLastIncrementalFlushMetaField;
igMetaField *g_igAttrStack_lastIncrementalFlushedAttrMetaField;
igMetaField *g_igAttrStack_hasChangedFromRootMetaField;
igMetaField *g_igAttrStack_lastFlushedAttrMetaField;
igMetaField *g_igAttrStack_cachedRenderPackageMetaField;

igMetaObject *igAttrStack_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrStack_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a5b90();
    return g_igAttrStack_metaObject;
}

int igAttrStack_GetVTable(void) {
    union U_1a5b00 u;
    void **q5;
    int temp_s0;
    void *temp_a0;

    igObject_InitHeader((igObject *)u.b);
    q5 = &u.p[5];
    u.w[0] = (int)(&g_igAttrStack_vtable[0]);
    *q5 = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.w[0] = (int)(&g_igAttrStack_vtable[0]);
    if (q5 != 0) {
        temp_a0 = *q5;
        if (temp_a0 != 0) {
            *(int *)((char *)(temp_a0) + 4) = (int)((int) (*(int *)((char *)(temp_a0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_a0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
    }
    return temp_s0;
}

void FUN_001a5b90(void)
{
    igMetaObject_RunStaticInit(igAttrStack_Register);
}

static igMetaObjectCallback g_igAttrStack_callbackList[] = { FUN_0013b110, FUN_0013b110, FUN_00197cc0, 0 };

CallbackArray *igAttrStack_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAttrStack_metaObject,
        igNonRefCountedObjectStack_Register,
        igNonRefCountedObjectStack_GetPublishedMetaObject,
        thunk_igAttrStack_GetMetaObject,
        "igAttrStack",
        0x34, /* instance size */
        igAttrStack_GetVTable,
        &igAttrStack_InitFields,
        0, /* extra callback item */
        g_igAttrStack_callbackList /* callback list */
    );
}

void thunk_igAttrStack_GetMetaObject(void) {
    igAttrStack_GetMetaObject();
}

static FieldFactory g_igAttrStack_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igAttrStack_fieldTable[] = {
    "_default",
    "_cachedOverride",
    "_popProc",
    "_hasChangedFromLastIncrementalFlush",
    "_lastIncrementalFlushedAttr",
    "_hasChangedFromRoot",
    "_lastFlushedAttr",
    "_cachedRenderPackage",
};
static igMetaField **g_igAttrStack_fieldHandles[] = {
    &g_igAttrStack_defaultMetaField,
    &g_igAttrStack_cachedOverrideMetaField,
    &g_igAttrStack_popProcMetaField,
    &g_igAttrStack_hasChangedFromLastIncrementalFlushMetaField,
    &g_igAttrStack_lastIncrementalFlushedAttrMetaField,
    &g_igAttrStack_hasChangedFromRootMetaField,
    &g_igAttrStack_lastFlushedAttrMetaField,
    &g_igAttrStack_cachedRenderPackageMetaField,
};
static int g_igAttrStack_fieldOffsets[] = {
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
};

void igAttrStack_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAttrStack_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igAttrStack_ctorTable, 8);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0013b070();
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1), -1);
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 4)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0013b070();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 6)));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0013b070();
    ((igObjectRefMetaField *)temp_s1_3)->_refCounted = 0;
    temp_s1_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 7)));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = (int)FUN_00197af0();
    ((igObjectRefMetaField *)temp_s1_4)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igAttrStack_fieldTable, g_igAttrStack_fieldHandles, g_igAttrStack_fieldOffsets, temp_s2);
}

