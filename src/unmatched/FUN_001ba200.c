int FUN_001b1030();
int FUN_001b1100();
int FUN_001b4c40();
typedef struct { char pad[52]; int f34; char pad2[176]; int fe8; } T;
int FUN_001ba200(int arg0_, int arg1) {
    T *arg0 = (T *)arg0_;
    FUN_001b1030(arg0->f34, arg0->fe8);
    FUN_001b4c40(arg1, arg0);
    FUN_001b1100(arg0->f34, arg0->fe8);
    return 0;
}
