igMetaObject *igObjectStringMap_GetOrCreateMetaObject(void) {
    if (g_igObjectStringMap_metaObject[0] == 0) {
        g_igObjectStringMap_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igObjectStringMap_metaObject[0];
}

igMetaObject *igObjectStringMap_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectStringMap_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igObjectStringMap_EnsureRegistered();
    return g_igObjectStringMap_metaObject[0];
}

int igObjectStringMap_GetVTable(void) {
    igObjectStringMap map;
    int t;
    igObject *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;
    int *q8;
    int *q12;
    igObject_InitHeader((igObject *)&map);
    map._vtable = (int)&DAT_00532d80[0];
    q8 = &map._names;
    *q8 = 0;
    q12 = &map._data;
    *q12 = 0;
    t = *(int *)((char *)&map + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    map._vtable = (int)&DAT_00532d80[0];
    if (q12 != 0) {
        o = (igObject *)*q12;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    if (q8 != 0) {
        o = (igObject *)*q8;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}

void igObjectStringMap_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igObjectStringMap_Register);
}

void igObjectStringMap_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igObjectStringMap_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igObjectStringMap_GetMetaObjectFunction,
        igObjectStringMap_className,
        0x10, /* instance size */
        igObjectStringMap_GetVTable,
        &igObjectStringMap_InitFields,
        0, /* extra callback item */
        g_igObjectStringMap_callbackList /* callback list */
    );
}

void igObjectStringMap_GetMetaObjectFunction(void) {
    igObjectStringMap_GetMetaObject();
}

void igObjectStringMap_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igObjectStringMap_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igObjectStringMap_ctorTable[0], 2);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igObjectStringMap_fieldTable[0], (igMetaField ***)&DAT_004bfa98[0], &DAT_004bfaa0[0], temp_s2);
}

