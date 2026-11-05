extern "C" {
int igObject_IsKindOf(void *, int);
int Matrix44_Copy(int, int);
extern int DAT_00561000[4];
}
struct O {
    char pad[8]; int f8;
    static inline O *Cast(O *p) {
        if (p != 0 && igObject_IsKindOf(p, DAT_00561000[0]) != 0) {
            return p;
        }
        return 0;
    }
};
extern "C" int FUN_0022d460(O *arg0, int arg1, O *arg2, int arg3) {
    O *s3 = O::Cast(arg0);
    O *s1 = O::Cast(arg2);
    if (s3 != 0 && s1 != 0) {
        Matrix44_Copy(arg3 + s1->f8, arg1 + s3->f8);
        return 1;
    }
    return 0;
}
