igMetaObject *igCallStackTable_GetOrCreateMetaObject(void) {
    if (g_igCallStackTable_metaObject[0] == 0) {
        g_igCallStackTable_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igCallStackTable_metaObject[0];
}

igMetaObject *igCallStackTable_GetMetaObject(void)
{
    igMetaObject *g = g_igCallStackTable_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igCallStackTable_EnsureRegistered();
    return g_igCallStackTable_metaObject[0];
}

int igCallStackTable_GetVTable(void) {
    igCallStackTable table;
    int vtable;
    igObject *q0;
    igObject *q1;

    igObject_InitHeader((igObject *)&table);
    table._vtable = (int)&g_igCallStackTable_vtable[0];
    q1 = (igObject *)&table._callStacks;
    *(int *)q1 = 0;
    q0 = (igObject *)&table._hashIndex;
    *(int *)q0 = 0;
    vtable = *(int *)((char *)&table + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    table._vtable = (int)&g_igCallStackTable_vtable[0];
    if (q0 != 0) {
        q0 = *(igObject **)q0;
        if (q0 != 0) {
            q0->_refCount = (int)((int) (q0->_refCount - 1));
            if (((unsigned long long) ((long long)(int) q0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(igObject **)q1;
        if (q1 != 0) {
            q1->_refCount = (int)((int) (q1->_refCount - 1));
            if (((unsigned long long) ((long long)(int) q1->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return vtable;
}

void igCallStackTable_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igCallStackTable_Register);
}

void igCallStackTable_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igCallStackTable_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igCallStackTable_GetMetaObjectFunction,
        igCallStackTable_className,
        0x18,
        igCallStackTable_GetVTable,
        igCallStackTable_InitFields,
        0,
        (igMetaObjectCallback *)g_igCallStackTable_callbackList
    );
}

void igCallStackTable_GetMetaObjectFunction(void) {
    igCallStackTable_GetMetaObject();
}

void igCallStackTable_InitFields(void) {
    int base;
    void *hashIndex;
    void *callStacks;
    void *meta;

    meta = (void *)g_igCallStackTable_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igCallStackTable_ctorTable[0], 4);
    callStacks = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)callStacks)->_metaObject = (int)igUnsignedIntListNoClean_GetOrCreateMetaObject();
    ((igRefMetaField *)callStacks)->_construct = 1;
    hashIndex = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    ((igObjectRefMetaField *)hashIndex)->_metaObject = (int)igIntListNoClean_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igCallStackTable_fieldTable[0], (igMetaField ***)&g_igCallStackTable_fieldDescriptors[0], &g_igCallStackTable_fieldOffsets[0], base);
}

