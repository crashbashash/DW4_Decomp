void igStringTable_Create(int arg0) {
    igStringTable_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5858B0), (igMemoryPoolView *)arg0);
}

igMetaObject *igStringTable_GetOrCreateMetaObject(void) {
    if (g_igStringTable_metaObject[0] == 0) {
        g_igStringTable_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igStringTable_metaObject[0];
}

igMetaObject *igStringTable_GetMetaObject(void)
{
    igMetaObject *g = g_igStringTable_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igStringTable_EnsureRegistered();
    return g_igStringTable_metaObject[0];
}

int igStringTable_GetVTable(void) {
    igStringTable table;
    int r;
    int *strings;
    int *hashIndex;

    igObject_InitHeader((igObject *)&table);
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

igObject **igSmartPointer_igCharListNoClean_Destruct(igObject **arg0, short arg1) {
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

void igStringTable_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStringTable_Register);
}

void igStringTable_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igStringTable_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igStringTable_GetMetaObjectFunction,
        igStringTable_className,
        0x18, /* instance size */
        igStringTable_GetVTable,
        &igStringTable_InitFields,
        0, /* extra callback item */
        g_igStringTable_callbackList /* callback list */
    );
}

void igStringTable_GetMetaObjectFunction(void) {
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
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igCharListNoClean_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)igIntListNoClean_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igStringTable_fieldTable[0], (igMetaField ***)&DAT_004bf650[0], &DAT_004bf660[0], temp_s2);
}

