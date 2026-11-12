void FUN_00344e40(int arg0) {
    FUN_00345010();
    igMetaObject_CreateInstance(*(int *)0x587F10, arg0);
}

int FUN_00344e80(void) {
    if (((int *)DAT_00587f10)[0] == 0) {
        ((int *)DAT_00587f10)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00587f10)[0];
}

void *FUN_00344ed0(void) {
    struct G *g = DAT_00587f10[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00345010();
    }
    return DAT_00587f10[0];
}

int beShadow01_GetVTable(void) {
    struct W o;
    int r;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[5] = 0;
    o.vt = DAT_0053b330;
    o.f[7] = 0;
    r = *(int *)((char *)&o + *(int *)(((char * *)DAT_00586dc8)[0] + 916));
    o.vt = DAT_0053b330;
    FUN_00344f90((struct R **)(&o.f[7]), (short)(-1));
    FUN_0033f5e0((O_33f5e0 *)&o, (short)0);
    return r;
}

struct R **FUN_00344f90(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_00345010(void)
{
    igMetaObject_RunStaticInit(beShadow01_Register);
}

void *beShadow01_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beShadow01_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beShadow01_GetMetaObject,
        beShadow01_className,
        0x30, /* instance size */
        beShadow01_GetVTable,
        beShadow01_InitFields,
        0, /* extra callback item */
        g_beShadow01_callbackList /* callback list */
    );
}

void beShadow01_GetMetaObject(void)
{
    FUN_00344ed0();
}

void beShadow01_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00587f10)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3a48[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_003449b0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c3a50[0], &DAT_004c3a58[0], &DAT_004c3a60[0], temp_s2);
}

