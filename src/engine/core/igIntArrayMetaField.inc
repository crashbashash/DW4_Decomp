void igIntArrayMetaField_Create(int arg0) {
    igIntArrayMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586108), (igMemoryPoolView *)arg0);
}

igMetaObject *igIntArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igIntArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igIntArrayMetaField_EnsureRegistered();
    return g_igIntArrayMetaField_metaObject[0];
}

int igIntArrayMetaField_GetVTable(void) {
    igIntArrayMetaField obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igIntMetaField_Init((igMetaField *)&obj);
    obj._vtable = (int)&DAT_0052fce0[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    obj._vtable = (int)&g_igMetaField_vtable[0];
    if (&obj._fieldName != 0) {
        o = (char *)obj._fieldName;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*a1), (int)a1);
            }
        }
    }
    return t;
}

void igIntArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igIntArrayMetaField_Register);
}

void igIntArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igIntArrayMetaField_metaObject),
        igIntMetaField_Register,
        igIntMetaField_GetPublishedMetaObject,
        igIntArrayMetaField_GetMetaObjectFunction,
        igIntArrayMetaField_className,
        0x38, /* instance size */
        igIntArrayMetaField_GetVTable,
        &igIntArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igIntArrayMetaField_callbackList /* callback list */
    );
}

void igIntArrayMetaField_GetMetaObjectFunction(void) {
    igIntArrayMetaField_GetMetaObject();
}

igMetaObject *igIntMetaField_GetPublishedMetaObject(void) {
    return g_igIntMetaField_metaObject[0];
}

void igIntArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igIntArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igIntArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igIntArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004c0600[0], &DAT_004c0608[0], temp_s1);
}

void igIntArrayMetaField_CreateDefaultDescriptor(void) {
    igIntArrayMetaField *temp_s0;
    igIntArrayMetaField *g;

    if (DAT_00586110[0] == 0) {
        DAT_00586110[0] = (igIntArrayMetaField *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igIntArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        temp_s0 = DAT_00586110[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)temp_s0);
            g = DAT_00586110[0];
            g->_refCount = g->_refCount - 1;
            if ((g->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(g);
            }
            DAT_00586110[0]->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00586110[0]);
        }
    }
}

