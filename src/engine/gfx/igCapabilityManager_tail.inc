void Gap__Gfx__igCapabilityManager__vfunc_24(V *arg0, int arg1) {
    T27 sp140 = DAT_0048a180;
    T27 spD0 = DAT_0048a1f0;
    char sp50[128];
    int i;
    for (i = 0; i < 27; i++) {
        sprintf(sp50, DAT_004de6a8, arg0->vX(sp140.v[i]));
        FUN_002d9740(arg1, 8, spD0.v[i], sp50);
    }
}

