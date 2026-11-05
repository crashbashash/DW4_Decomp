extern "C" int igObject_IsKindOf(...);
extern "C" void *DAT_00586638[4];
struct S_a { char pad0[8]; int f8; };
struct K { 
  S_a *Cast(void *p) {
    if (p != 0 && igObject_IsKindOf(p, DAT_00586638[0]) != 0) { return (S_a *)p; }
    return 0;
  }
};
extern "C" int FUN_0022dfe0(void *arg0, int arg1, void *arg2, int arg3) {
    K k;
    S_a *var_s3 = k.Cast(arg0);
    S_a *var_s1 = k.Cast(arg2);
    if (var_s3 != 0 && var_s1 != 0) {
        *(long long *)(arg3 + var_s1->f8) = *(long long *)(arg1 + var_s3->f8);
        return 1;
    }
    return 0;
}
