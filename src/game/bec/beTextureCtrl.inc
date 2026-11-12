void FUN_00342310(int arg0) {
    FUN_003424e0();
    igMetaObject_CreateInstance(*(int *)0x587CB8, arg0);
}

int FUN_00342350(void) {
    if (((int *)DAT_00587cb8)[0] == 0) {
        ((int *)DAT_00587cb8)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00587cb8)[0];
}

void *FUN_003423a0(void) {
    struct G *g = DAT_00587cb8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003424e0();
    }
    return DAT_00587cb8[0];
}

int beTextureCtrl_GetVTable(void) {
    Obj_3423f0 o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[5] = 0;
    o.vt = &DAT_0053c300[0];
    o.s = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0053c300[0];
    FUN_00342460((void **)&o.s, (short)(-1));
    FUN_0033f5e0((O_33f5e0 *)&o, (short)0);
    return r;
}

void **FUN_00342460(void **arg0, short arg1) {
    S_temp_a0_342460 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_342460 *)(*arg0);
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

void FUN_003424e0(void)
{
    igMetaObject_RunStaticInit(beTextureCtrl_Register);
}

void *beTextureCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTextureCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beTextureCtrl_GetMetaObject,
        beTextureCtrl_className,
        0x28, /* instance size */
        beTextureCtrl_GetVTable,
        beTextureCtrl_InitFields,
        0, /* extra callback item */
        g_beTextureCtrl_callbackList /* callback list */
    );
}

void beTextureCtrl_GetMetaObject(void)
{
    FUN_003423a0();
}

void beTextureCtrl_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00587cb8)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c34e8[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00342670();
    igMetaObject_NameFields(temp_s0, &DAT_004c34f0[0], &DAT_004c34f8[0], &DAT_004c3500[0], temp_s2);
}

