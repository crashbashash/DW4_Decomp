void * igMemoryDictionary_Create(int arg0) {
    igMemoryDictionary_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585FA0), (igMemoryPoolView *)arg0));
}

igMetaObject *igMemoryDictionary_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryDictionary_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryDictionary_EnsureRegistered();
    return g_igMemoryDictionary_metaObject[0];
}

int igMemoryDictionary_GetVTable(void) {
    igMemoryDictionary dictionary;
    int **pr;
    int temp_s0;
    int *o;

    igObject_InitHeader((igObject *)&dictionary);
    dictionary._vtable = (int)&DAT_0052f910[0];
    pr = (int **)&dictionary._memoryEntries;
    *pr = 0;
    temp_s0 = *(int *)((char *)&dictionary + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    dictionary._vtable = (int)&DAT_0052f910[0];
    if (pr != 0) {
        if (*pr != 0) {
            o = *pr;
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return temp_s0;
}

void igMemoryDictionary_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryDictionary_Register);
}

void igMemoryDictionary_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMemoryDictionary_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igMemoryDictionary_GetMetaObjectFunction,
        igMemoryDictionary_className,
        0x18, /* instance size */
        igMemoryDictionary_GetVTable,
        &igMemoryDictionary_InitFields,
        0, /* extra callback item */
        g_igMemoryDictionary_callbackList /* callback list */
    );
}

void igMemoryDictionary_GetMetaObjectFunction(void) {
    igMemoryDictionary_GetMetaObject();
}

void igMemoryDictionary_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igMemoryDictionary_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igMemoryDictionary_ctorTable[0], 4);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igUnsignedIntListNoClean_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_construct = 1;
    *(char *)((char *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3))) + 38) = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igMemoryDictionary_fieldTable[0], (igMetaField ***)&DAT_004c03b0[0], &DAT_004c03c0[0], temp_s2);
}

