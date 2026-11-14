void FUN_002b8d50(int arg0) {
    FUN_002b8f90();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x5858B0), (MemoryPool *)arg0);
}

igMetaObject *FUN_002b8d90(void) {
    if (g_igStringTable_metaObject[0] == 0) {
        g_igStringTable_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igStringTable_metaObject[0];
}

igMetaObject *igStringTable_GetMetaObject(void)
{
    igMetaObject *g = g_igStringTable_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b8f90();
    return g_igStringTable_metaObject[0];
}

int igStringTable_GetVTable(void) {
    igStringTable table;
    int r;
    int *strings;
    int *hashIndex;

    igObject_InitHeader((struct ObjectHeader *)&table);
    table._vtable = (int)&DAT_0052e8c0[0];
    strings = &table._strings;
    *strings = 0;
    hashIndex = &table._hashIndex;
    *hashIndex = 0;
    r = *(int *)((char *)&table + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    table._vtable = (int)&DAT_0052e8c0[0];
    ReleaseObjectField(hashIndex);
    ReleaseObjectField(strings);
    return r;
}

igObject **FUN_002b8f10(igObject **arg0, short arg1) {
    igObject *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->_refCount = temp_a0->_refCount - 1;
            if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_002b8f90(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStringTable_Register);
}

void igStringTable_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igStringTable_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igStringTable_GetMetaObject,
        igStringTable_className,
        0x18, /* instance size */
        igStringTable_GetVTable,
        &igStringTable_InitFields,
        0, /* extra callback item */
        g_igStringTable_callbackList /* callback list */
    );
}

void thunk_igStringTable_GetMetaObject(void) {
    igStringTable_GetMetaObject();
}

void igStringTable_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igStringTable_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igStringTable_ctorTable[0], 4);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_002cace0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_002ca8f0();
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igStringTable_fieldTable[0], (igMetaField ***)&DAT_004bf650[0], &DAT_004bf660[0], temp_s2);
}

