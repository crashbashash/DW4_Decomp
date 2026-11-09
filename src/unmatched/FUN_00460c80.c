typedef struct R { char pad[4]; int f4; } R;
typedef struct A { char pad[32]; int f32; } A;
int FUN_0013ba30();
int FUN_0013c060();
int FUN_00460be0();
int ObjectList_AppendRetained();
int ObjectList_RemoveFirstRetained();
int igObject_Destroy();

int FUN_00460c80(R *arg0, A *arg1) {
    R *sp3C;
    R *volatile sp38;
    int sp34;
    int temp_v0;
    R *t;
    R *t2;

    temp_v0 = FUN_00460be0();
    if (temp_v0 != 0) {
        ObjectList_RemoveFirstRetained(&sp34, arg1->f32, temp_v0, 0);
        sp38 = arg0;
        t = sp38;
        if (t != 0) {
            t->f4 = t->f4 + 1;
        }
        FUN_0013ba30(&sp3C, FUN_0013c060(), &sp38);
        t = sp38;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            t2 = sp38;
            if (((unsigned long long) ((long long) t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t2);
            }
        }
        ObjectList_AppendRetained(arg1->f32, sp3C);
        t = sp3C;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        return 1;
    }
    return 0;
}
