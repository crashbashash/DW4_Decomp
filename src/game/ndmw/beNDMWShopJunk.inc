void FUN_003b6310(int arg0) {
    FUN_003b64f0();
    igMetaObject_CreateInstance(*(int *)0x58AC88, arg0);
}

void *FUN_003b6350(void) {
    struct G *g = DAT_0058ac88[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b64f0();
    }
    return DAT_0058ac88[0];
}

int beNDMWShopJunk_GetVTable(void) {
    struct Obj_3b63a0 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f34 = 0;
    obj.f38 = 0;
    obj.f3C = 0;
    obj.f40 = 0;
    obj.f44 = 0;
    obj.f48 = 0;
    obj.f4C = 0;
    obj.vt = (&DAT_0053fcd0[0]);
    obj.f5C = 0;
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_0053fcd0[0]);
    FUN_003b6090((void **)&obj.f5C, (long long)(-1));
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return temp_s0;
}

