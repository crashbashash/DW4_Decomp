void FUN_0034ce50(int arg0) {
    FUN_0034cf20();
    igMetaObject_CreateInstance(*(int *)0x588550, arg0);
}

void *FUN_0034ce90(void) {
    struct G *g = DAT_00588550[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034cf20();
    }
    return DAT_00588550[0];
}

int bePadData_GetVTable(void) {
    struct Obj_34cee0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053afd0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0034cf20(void)
{
    igMetaObject_RunStaticInit(bePadData_Register);
}

void *bePadData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_bePadData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        bePadData_GetMetaObject,
        bePadData_className,
        0x68, /* instance size */
        bePadData_GetVTable,
        bePadData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void bePadData_GetMetaObject(void)
{
    FUN_0034ce90();
}

void bePadData_InitFields(void) {
    int sp38[2];
    int sp30[2];
    int temp_a0;
    int temp_a0_2;
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00588550)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4740[0], 0x16);
    temp_a0 = ((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    sp38[0] = 0;
    sp38[1] = 0;
    FUN_0018e2f0(temp_a0, sp38);
    temp_a0_2 = ((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    sp30[0] = 0;
    sp30[1] = 0;
    FUN_0018e2f0(temp_a0_2, sp30);
    igMetaObject_NameFields(temp_s0, &DAT_004c47a0[0], &DAT_004c4800[0], &DAT_004c4860[0], temp_s1);
}

