void * FUN_002baff0(int arg0) {
    FUN_002bb200();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585A08), (igMemoryPoolView *)arg0));
}

igMetaObject *FUN_002bb030(void) {
    if (g_igRegistry_metaObject[0] == 0) {
        g_igRegistry_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igRegistry_metaObject[0];
}

igMetaObject *igRegistry_GetMetaObject(void)
{
    igMetaObject *g = g_igRegistry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bb200();
    return g_igRegistry_metaObject[0];
}

int igRegistry_GetVTable(void) {
    igRegistry registry;
    int temp_s0;
    igObject *q0;
    igObject *q1;
    igObject *q2;

    igObject_InitHeader((igObject *)&registry);
    registry._vtable = (int)&DAT_0052ebf0[0];
    q2 = (igObject *)&registry._valueTable;
    *(int *)q2 = 0;
    q1 = (igObject *)&registry._registryFile;
    *(int *)q1 = 0;
    q0 = (igObject *)&registry._additionalSectionNames;
    *(int *)q0 = 0;
    temp_s0 = *(int *)((char *)&registry + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    registry._vtable = (int)&DAT_0052ebf0[0];
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
    return temp_s0;
}

void FUN_002bb200(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igRegistry_Register);
}

void igRegistry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igRegistry_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igRegistry_GetMetaObject,
        igRegistry_className,
        0x18, /* instance size */
        igRegistry_GetVTable,
        &igRegistry_InitFields,
        0, /* extra callback item */
        g_igRegistry_callbackList /* callback list */
    );
}

void thunk_igRegistry_GetMetaObject(void) {
    igRegistry_GetMetaObject();
}

void igRegistry_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s1;

    temp_s1 = (void *)g_igRegistry_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, (igMetaField * (**)(void *))&g_igRegistry_ctorTable[0], 5);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_002bb390();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_002c4ce0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_002b9390();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    FUN_002d3890((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4))), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s1, (const char **)&g_igRegistry_fieldTable[0], (igMetaField ***)&DAT_004bf8d0[0], &DAT_004bf8f0[0], temp_s0);
}

