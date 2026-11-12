void FUN_00133610(int arg0) {
    FUN_001336e0();
    igMetaObject_CreateInstance(*(int *)0x55EE50, arg0);
}

igMetaObject *igStencilFunctionAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igStencilFunctionAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001336e0();
    return g_igStencilFunctionAttr_metaObject[0];
}

int igStencilFunctionAttr_GetVTable(void) {
    struct Obj_1336a0 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00522e20[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001336e0(void)
{
    igMetaObject_RunStaticInit(igStencilFunctionAttr_Register);
}

void igStencilFunctionAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStencilFunctionAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igStencilFunctionAttr_GetMetaObject,
        igStencilFunctionAttr_className,
        0x28, /* instance size */
        igStencilFunctionAttr_GetVTable,
        &igStencilFunctionAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igStencilFunctionAttr_GetMetaObject(void) {
    igStencilFunctionAttr_GetMetaObject();
}

void igStencilFunctionAttr_InitFields(void) {
    void *temp_s1;
    int temp_s0;
    void *temp_v0;

    temp_s1 = (void *)g_igStencilFunctionAttr_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_00485e70[0], 7);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    FUN_002dc7a0(temp_v0, &DAT_00485ef0[0]);
    *(void **)&((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (void *)FUN_00149500;
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2), -1);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3), -1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    FUN_002dc7a0(temp_v0, &DAT_00485ef8[0]);
    *(void **)&((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (void *)FUN_001494a0;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    FUN_002dc7a0(temp_v0, &DAT_00485f00[0]);
    *(void **)&((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (void *)FUN_001494a0;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    FUN_002dc7a0(temp_v0, &DAT_00485f08[0]);
    *(void **)&((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (void *)FUN_001494a0;
    igMetaObject_NameFields(temp_s1, &DAT_00485e90[0], &DAT_00485eb0[0], &DAT_00485ed0[0], temp_s0);
}

void **FUN_001338d0(void **arg0, short arg1) {
    S_temp_a0_1338d0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_1338d0 *)((void *)(*arg0));
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

