void FUN_002cdf30(int arg0) {
    FUN_002ce050();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586B20), (MemoryPool *)arg0);
}

igMetaObject *igStackMemoryPool_GetMetaObject(void)
{
    igMetaObject *g = g_igStackMemoryPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002ce050();
    return g_igStackMemoryPool_metaObject[0];
}

int igStackMemoryPool_GetVTable(void) {
    Obj_2cdfc0 obj;
    int r;

    igMemoryPool_Initialize((int **)&obj);
    obj.vt = &DAT_0052de80[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    obj.vt = &DAT_0052de80[0];
    obj.release();
    return r;
}

void FUN_002ce050(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStackMemoryPool_Register);
}

void igStackMemoryPool_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igStackMemoryPool_metaObject),
        igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        thunk_igStackMemoryPool_GetMetaObject,
        igStackMemoryPool_className,
        0x98, /* instance size */
        igStackMemoryPool_GetVTable,
        &igStackMemoryPool_InitFields,
        0, /* extra callback item */
        g_igStackMemoryPool_callbackList /* callback list */
    );
}

void thunk_igStackMemoryPool_GetMetaObject(void) {
    igStackMemoryPool_GetMetaObject();
}

void igStackMemoryPool_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igStackMemoryPool_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004c1950[0], 0xA);
    FUN_002ea4b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2))), -1);
    FUN_0030eda0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1))), 4);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 9)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_002c57c0();
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004c1980[0], (igMetaField ***)&DAT_004c19b0[0], &DAT_004c19e0[0], temp_s2);
}

