void FUN_003442b0(int arg0) {
    FUN_003444c0();
    igMetaObject_CreateInstance(*(int *)0x587EA8, arg0);
}

int FUN_003442f0(void) {
    if (((int *)DAT_00587ea8)[0] == 0) {
        ((int *)DAT_00587ea8)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00587ea8)[0];
}

S_344340 *FUN_00344340(void) {
    S_344340 *g = DAT_00587ea8[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_003444c0();
done:
    return DAT_00587ea8[0];
}

int beSound_GetVTable(void) {
    struct W o;
    int *p16;
    int r;
    int *p17;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[5] = 0;
    o.vt = &DAT_0053b3d0[0];
    p16 = &o.f[7];
    *p16 = 0;
    p17 = &o.f[8];
    *p17 = 0;
    o.f[9] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0053b3d0[0];
    FUN_00344440((void **)(&o.f[9]), (short)(-1));
    StringRef_Destruct_00130720(p17, -1);
    FUN_0033de20((void **)p16, (short)(-1));
    FUN_0033f5e0((O_33f5e0 *)&o, (short)0);
    return r;
}

void **FUN_00344440(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_003444c0(void)
{
    igMetaObject_RunStaticInit(beSound_Register);
}

void *beSound_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSound_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beSound_GetMetaObject,
        beSound_className,
        0x2c, /* instance size */
        beSound_GetVTable,
        beSound_InitFields,
        0, /* extra callback item */
        g_beSound_callbackList /* callback list */
    );
}

void beSound_GetMetaObject(void)
{
    FUN_00344340();
}

void beSound_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00587ea8)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3980[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_003678a0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00344630();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c3990[0], &DAT_004c39a0[0], &DAT_004c39b0[0], temp_s2);
}

