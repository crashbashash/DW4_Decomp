void FUN_00357660(int arg0) {
    FUN_00357820();
    igMetaObject_CreateInstance(*(int *)0x588F30, arg0);
}

int FUN_003576a0(void) {
    if (DAT_00588f30[0] == 0) {
        DAT_00588f30[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00588f30[0];
}

void *FUN_003576f0(void) {
    unsigned char b;
    if (((void * *)DAT_00588f30)[0] != 0) {
        b = (*(int *)((char *)(((void * *)DAT_00588f30)[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00357820();
done:
    return ((void * *)DAT_00588f30)[0];
}

int beMeterCtrl_GetVTable(void) {
    Obj_357740 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053a0d0[0];
    obj.r1 = 0;
    obj.r2 = 0;
    obj.vt = &DAT_0053abf0[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053a0d0[0];
    obj.rel2();
    obj.vt = &DAT_00524950[0];
    obj.rel1();
    return r;
}

void FUN_00357820(void)
{
    igMetaObject_RunStaticInit(beMeterCtrl_Register);
}

void *beMeterCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMeterCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beMeterCtrl_GetMetaObject,
        beMeterCtrl_className,
        0x20, /* instance size */
        beMeterCtrl_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beMeterCtrl_GetMetaObject(void)
{
    FUN_003576f0();
}

