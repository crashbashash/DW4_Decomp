igMetaObject *igMersenneTwisterRandomNumber_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igMersenneTwisterRandomNumber_metaObject[0] != 0) {
        ready = (g_igMersenneTwisterRandomNumber_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_001e4620();
done:
    return g_igMersenneTwisterRandomNumber_metaObject[0];
}

int igMersenneTwisterRandomNumber_GetVTable(void) {
    struct Obj_1e45e0 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052b8e0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001e4620(void)
{
    igMetaObject_RunStaticInit(igMersenneTwisterRandomNumber_Register);
}

void igMersenneTwisterRandomNumber_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMersenneTwisterRandomNumber_metaObject,
        igRandomNumber_Register,
        igRandomNumber_GetPublishedMetaObject,
        thunk_igMersenneTwisterRandomNumber_GetMetaObject,
        igMersenneTwisterRandomNumber_className,
        0x9CC, /* instance size */
        igMersenneTwisterRandomNumber_GetVTable,
        &igMersenneTwisterRandomNumber_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

int FUN_001e46a0(void) {
    return DAT_00562b70[0];
}

void igMersenneTwisterRandomNumber_InitFields(void) {
    int temp_s0;
    int temp_s1;
    struct F *f;

    temp_s0 = DAT_00562b88[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048daf0[0], 2);
    f = (struct F *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    f->f52 = 0x270;
    igMetaObject_NameFields(temp_s0, &DAT_0048daf8[0], &DAT_0048db00[0], &DAT_0048db08[0], temp_s1);
}

