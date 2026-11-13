void * FUN_002bfed0(int arg0) {
    FUN_002c00f0();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585E00), (MemoryPool *)arg0));
}

igMetaObject *igMemoryPoolInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPoolInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c00f0();
    return g_igMemoryPoolInfo_metaObject[0];
}

int igMemoryPoolInfo_GetVTable(void) {
    struct Obj_2bff60 obj;
    int t;
    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.w2 = 0;
    obj.vt = &DAT_0052f430[0];
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    obj.vt = &DAT_0052f430[0];
    StringRef_Destruct_00130720(&obj.w19, -1);
    StringRef_Destruct_00130720(&obj.w18, -1);
    StringRef_Destruct_00130720(&obj.w17, -1);
    StringRef_Destruct_00130720(&obj.w16, -1);
    StringRef_Destruct_00130720(&obj.w15, -1);
    StringRef_Destruct_00130720(&obj.w14, -1);
    StringRef_Destruct_00130720(&obj.w13, -1);
    StringRef_Destruct_00130720(&obj.w12, -1);
    StringRef_Destruct_00130720(&obj.w11, -1);
    StringRef_Destruct_00130720(&obj.w10, -1);
    StringRef_Destruct_00130720(&obj.w6, -1);
    StringRef_Destruct_00130720(&obj.w5, -1);
    FUN_00131b20(&obj, 0);
    return t;
}

void FUN_002c00f0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryPoolInfo_Register);
}

void igMemoryPoolInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMemoryPoolInfo_metaObject),
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igMemoryPoolInfo_GetMetaObject,
        igMemoryPoolInfo_className,
        0x54, /* instance size */
        igMemoryPoolInfo_GetVTable,
        &igMemoryPoolInfo_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMemoryPoolInfo_GetMetaObject(void) {
    igMemoryPoolInfo_GetMetaObject();
}

void igMemoryPoolInfo_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igMemoryPoolInfo_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igMemoryPoolInfo_ctorTable[0], 0x10);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igMemoryPoolInfo_fieldTable[0], (igMetaField ***)&DAT_004c00e0[0], &DAT_004c0120[0], temp_s1);
}

