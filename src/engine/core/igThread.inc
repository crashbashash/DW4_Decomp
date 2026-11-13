int FUN_002b7dc0(void) {
    if (DAT_005857a8[0] == 0) {
        DAT_005857a8[0] = ((int)igMetaEnum_Create((char *)&text_Priority[0], (char **)&DAT_004bf3a0[0], &DAT_004bf3c0[0], 6));
    }
    return DAT_005857a8[0];
}

int FUN_002b7e20(void) {
    if (DAT_005857b0[0] == 0) {
        DAT_005857b0[0] = ((int)igMetaEnum_Create((char *)&text_State[0], (char **)&DAT_004bf3d8[0], &DAT_004bf3e0[0], 2));
    }
    return DAT_005857b0[0];
}

int FUN_002b7e80(void) {
    if (DAT_005857b8[0] == 0) {
        DAT_005857b8[0] = ((int)igMetaEnum_Create((char *)&text_Scope[0], (char **)&DAT_004bf3e8[0], &DAT_004bf3f8[0], 3));
    }
    return DAT_005857b8[0];
}

int FUN_002b7ee0(void) {
    if (DAT_005857c0[0] == 0) {
        DAT_005857c0[0] = ((int)igMetaEnum_Create((char *)&text_Type[0], (char **)&DAT_004bf408[0], &DAT_004bf410[0], 2));
    }
    return DAT_005857c0[0];
}

void * FUN_002b7f40(int arg0) {
    FUN_002b8020();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x5857C8), (MemoryPool *)arg0));
}

igMetaObject *FUN_002b7f80(void) {
    if (g_igThread_metaObject[0] == 0) {
        g_igThread_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    }
    return g_igThread_metaObject[0];
}

igMetaObject *igThread_GetMetaObject(void)
{
    igMetaObject *g = g_igThread_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b8020();
    return g_igThread_metaObject[0];
}

void FUN_002b8020(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igThread_Register);
}

void igThread_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igThread_metaObject),
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igThread_GetMetaObject,
        igThread_className,
        0x30, /* instance size */
        0,
        &igThread_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igThread_GetMetaObject(void) {
    igThread_GetMetaObject();
}

void igThread_InitFields(void) {
    int temp_s0;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_s1;

    temp_s1 = (void *)(((void * *)g_igThread_metaObject)[0]);
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, (igMetaField * (**)(void *))&g_igThread_ctorTable[0], 0xA);
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0)));
    FUN_002dc7a0((igEnumMetaFieldView *)temp_v0, (const int *)&DAT_004bf4d8[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(FUN_002b7dc0);
    temp_v0_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1)));
    FUN_002dc7a0((igEnumMetaFieldView *)temp_v0_2, (const int *)&DAT_004bf4e0[0]);
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(&FUN_002b7ee0);
    temp_v0_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2)));
    FUN_002dc7a0((igEnumMetaFieldView *)temp_v0_3, (const int *)&DAT_004bf4e8[0]);
    ((igEnumMetaField *)temp_v0_3)->_getMetaEnumFunction = (int)(&FUN_002b7e80);
    temp_v0_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3)));
    FUN_002dc7a0((igEnumMetaFieldView *)temp_v0_4, (const int *)&DAT_004bf4f0[0]);
    ((igEnumMetaField *)temp_v0_4)->_getMetaEnumFunction = (int)(&FUN_002b7e20);
    FUN_0030e9b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 6))), 0x1000);
    igMetaObject_NameFields((igMetaObject *)temp_s1, (const char **)&g_igThread_fieldTable[0], (igMetaField ***)&DAT_004bf480[0], &DAT_004bf4b0[0], temp_s0);
    *(int *)((char *)(((void * *)g_igThread_metaObject)[0]) + 60) = (int)thunk_igPsx2Thread_GetMetaObject;
}

