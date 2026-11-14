igMetaObject *igMemoryRefArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryRefArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryRefArrayMetaField_EnsureRegistered();
    return g_igMemoryRefArrayMetaField_metaObject[0];
}

int igMemoryRefArrayMetaField_GetVTable(void) {
    igMemoryRefArrayMetaField obj;
    int vtable;

    igMemoryRefMetaField_Init((igMemoryRefMetaField *)&obj);
    obj._vtable = (int)&g_igMemoryRefArrayMetaField_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    obj._vtable = (int)&g_igMemoryRefArrayMetaField_vtable[0];
    igMemoryRefMetaField_Destroy((igMemoryRefMetaField *)&obj, (long long)0);
    return vtable;
}

void igMemoryRefArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryRefArrayMetaField_Register);
}

void igMemoryRefArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igMemoryRefArrayMetaField_metaObject,
        (igMetaObjectRegisterFunction)igMemoryRefMetaField_Register,
        (igMetaObjectGetFunction)igMemoryRefMetaField_GetPublishedMetaObject,
        igMemoryRefArrayMetaField_GetMetaObjectFunction,
        igMemoryRefArrayMetaField_className,
        0x54,
        igMemoryRefArrayMetaField_GetVTable,
        igMemoryRefArrayMetaField_InitFields,
        0,
        (igMetaObjectCallback *)g_igMemoryRefArrayMetaField_callbackList
    );
}

void igMemoryRefArrayMetaField_GetMetaObjectFunction(void) {
    igMemoryRefArrayMetaField_GetMetaObject();
}

int igMemoryRefMetaField_GetPublishedMetaObject(void) {
    return ((int *)g_igMemoryRefMetaField_metaObject)[0];
}

void igMemoryRefArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igMemoryRefArrayMetaField_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igMemoryRefArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igMemoryRefArrayMetaField_fieldTable[0], (igMetaField ***)&g_igMemoryRefArrayMetaField_fieldDescriptors[0], &g_igMemoryRefArrayMetaField_fieldOffsets[0], base);
}

void igMemoryRefArrayMetaField_CreateDefaultDescriptor(void) {
    igMemoryRefArrayMetaField *descriptor;
    igMemoryRefArrayMetaField *held;
    if (g_igMemoryRefArrayMetaField_descriptor[0] == 0) {
        g_igMemoryRefArrayMetaField_descriptor[0] = ((igMemoryRefArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igMemoryRefArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        descriptor = g_igMemoryRefArrayMetaField_descriptor[0];
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            held = g_igMemoryRefArrayMetaField_descriptor[0];
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
            g_igMemoryRefArrayMetaField_descriptor[0]->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igMemoryRefArrayMetaField_descriptor[0]);
        }
    }
}

