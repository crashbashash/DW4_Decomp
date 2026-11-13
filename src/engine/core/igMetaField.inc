igMetaObject *FUN_002beca0(void) {
    if (g_igMetaField_metaObject[0] == 0) {
        g_igMetaField_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_memoryContextMetaData)));
    }
    return g_igMetaField_metaObject[0];
}

igMetaObject *igMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bed40();
    return g_igMetaField_metaObject[0];
}

void FUN_002bed40(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMetaField_Register);
}

void igMetaField_Register(void) {
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igMetaField_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMetaField_GetMetaObject,
        igMetaField_className,
        0x34, /* instance size */
        0,
        &igMetaField_InitFields,
        0, /* extra callback item */
        g_igMetaField_callbackList /* callback list */
    );
}

void thunk_igMetaField_GetMetaObject(void) {
    igMetaField_GetMetaObject();
}

void igMetaField_InitFields(void) {
    int temp_s0;
    struct Fld *temp_s2;
    struct Fld *temp_v0_3;
    struct Fld *temp_v0_4;
    struct Fld *temp_v0;
    struct Fld *temp_v0_2;
    void *temp_s1;

    temp_s1 = (void *)g_igMetaField_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, (igMetaField * (**)(void *))&g_igMetaField_ctorTable[0], 0x12);
    ((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0))->f38 = 0;
    temp_v0 = ((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2));
    FUN_0030a520((void **)temp_v0, -1);
    temp_v0->f38 = 0;
    temp_v0_2 = ((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3));
    FUN_0030a520((void **)temp_v0_2, -1);
    temp_v0_2->f38 = 0;
    ((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4))->f38 = 0;
    temp_s2 = ((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5));
    temp_s2->f56 = (int)FUN_002be610();
    temp_s2->f60 = 0;
    temp_s2->f38 = 0;
    temp_s2->f40 = 1;
    temp_s2->f39 = 1;
    temp_v0_3 = ((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 6));
    temp_v0_3->f38 = 0;
    temp_v0_3->f40 = 1;
    temp_v0_4 = ((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 7));
    temp_v0_4->f53 = 1;
    temp_v0_4->f64 = 1;
    temp_v0_4->f65 = 1;
    temp_v0_4->f38 = 0;
    FUN_002d4e40((void **)(((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 8))), 0);
    FUN_002d3890((void **)(((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xA))), 1);
    FUN_002d4e40((void **)(((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xB))), 1);
    FUN_002d4e40((void **)(((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xC))), 0);
    FUN_002d4e40((void **)(((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xD))), 0);
    FUN_002d4e40((void **)(((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xE))), 0);
    FUN_002d4e40((void **)(((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xF))), 1);
    FUN_002d4e40((void **)(((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0x10))), 2);
    ((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0x11))->f38 = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, (const char **)&g_igMetaField_fieldTable[0], (igMetaField ***)&DAT_004bfea0[0], &DAT_004bfef0[0], temp_s0);
}

