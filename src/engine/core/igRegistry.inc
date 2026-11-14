void * igRegistry_Create(int pool) {
    igRegistry_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585A08), (igMemoryPoolView *)pool));
}

igMetaObject *igRegistry_GetOrCreateMetaObject(void) {
    if (g_igRegistry_metaObject[0] == 0) {
        g_igRegistry_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igRegistry_metaObject[0];
}

igMetaObject *igRegistry_GetMetaObject(void)
{
    igMetaObject *g = g_igRegistry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRegistry_EnsureRegistered();
    return g_igRegistry_metaObject[0];
}

int igRegistry_GetVTable(void) {
    igRegistry registry;
    int vtable;
    igObject *q0;
    igObject *q1;
    igObject *q2;

    igObject_InitHeader((igObject *)&registry);
    registry._vtable = (int)&g_igRegistry_vtable[0];
    q2 = (igObject *)&registry._valueTable;
    *(int *)q2 = 0;
    q1 = (igObject *)&registry._registryFile;
    *(int *)q1 = 0;
    q0 = (igObject *)&registry._additionalSectionNames;
    *(int *)q0 = 0;
    vtable = *(int *)((char *)&registry + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    registry._vtable = (int)&g_igRegistry_vtable[0];
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
    if (q2 != 0) {
        q2 = *(igObject **)q2;
        if (q2 != 0) {
            q2->_refCount = (int)((int) (q2->_refCount - 1));
            if (((unsigned long long) ((long long)(int) q2->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    return vtable;
}

void igRegistry_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igRegistry_Register);
}

void igRegistry_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igRegistry_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igRegistry_GetMetaObjectFunction,
        igRegistry_className,
        0x18,
        igRegistry_GetVTable,
        igRegistry_InitFields,
        0,
        (igMetaObjectCallback *)g_igRegistry_callbackList
    );
}

void igRegistry_GetMetaObjectFunction(void) {
    igRegistry_GetMetaObject();
}

void igRegistry_InitFields(void) {
    int first;
    void *valueTableField;
    void *registryFileField;
    void *sectionNamesField;
    void *meta;

    meta = (void *)g_igRegistry_metaObject[0];
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igRegistry_ctorTable[0], 5);
    valueTableField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first)));
    ((igObjectRefMetaField *)valueTableField)->_metaObject = (int)igRegistryValueList_GetOrCreateMetaObject();
    ((igRefMetaField *)valueTableField)->_construct = 1;
    registryFileField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 1)));
    ((igObjectRefMetaField *)registryFileField)->_metaObject = (int)igFile_GetOrCreateMetaObject();
    ((igRefMetaField *)registryFileField)->_construct = 1;
    sectionNamesField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 2)));
    ((igObjectRefMetaField *)sectionNamesField)->_metaObject = (int)igStringObjList_GetOrCreateMetaObject();
    ((igRefMetaField *)sectionNamesField)->_construct = 1;
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 4))), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igRegistry_fieldTable[0], (igMetaField ***)&g_igRegistry_fieldDescriptors[0], &g_igRegistry_fieldOffsets[0], first);
}

