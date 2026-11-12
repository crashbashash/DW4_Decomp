void *FUN_00368f80(void) {
    bool ok;
    if (DAT_00589be8[0] == 0) goto make;
    ok = !!(DAT_00589be8[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_00369060();
done:;
    return DAT_00589be8[0];
}

int beCameraDemoData_GetVTable(void) {
    Obj_368fd0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00534a30[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00534a30[0];
    obj.release();
    return r;
}

void FUN_00369060(void)
{
    igMetaObject_RunStaticInit(beCameraDemoData_Register);
}

void *beCameraDemoData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCameraDemoData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCameraDemoData_GetMetaObject,
        beCameraDemoData_className,
        0x20, /* instance size */
        beCameraDemoData_GetVTable,
        beCameraDemoData_InitFields,
        0, /* extra callback item */
        g_beCameraDemoData_callbackList /* callback list */
    );
}

void beCameraDemoData_GetMetaObject(void)
{
    FUN_00368f80();
}

void beCameraDemoData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00589be8)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7880[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0019f670();
    igMetaObject_NameFields(temp_s0, &DAT_004c7890[0], &DAT_004c78a0[0], &DAT_004c78b0[0], temp_s2);
}

