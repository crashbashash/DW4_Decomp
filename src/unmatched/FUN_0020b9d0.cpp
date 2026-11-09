extern "C" {
int FUN_00113f20(...);
int FUN_00113f78(...);
int FUN_001eff60(...);
int FUN_001effc0(...);
int FUN_00208430(...);
extern long long * DAT_00568f04[4];
void FUN_0020b9d0(void *arg0);
}
struct B { long long m : 7; };
struct N {
    char pad0[8];
    long long f8;
    char pad1[16];
    N *f32;
    N *f36;
    char pad2[30];
    char m : 7;
    char hi : 1;
    char f71;
    char f72;
    void Set() {
        m = 4;
        f8 = *DAT_00568f04[0];
        FUN_001effc0(1, &FUN_00208430, this);
    }
};
void FUN_0020b9d0(void *arg0) {
    N *n = (N *)arg0;
    N *var_s0;
    N *c;
    int a1;
    a1 = (n->f36 != 0) + 1;
    var_s0 = n->f32;
    int t = n->f71 + a1;
    if (n->f72 == 0) {
        FUN_001eff60(t, a1);
        FUN_00113f20();
        n->Set();
        c = n->f36;
        if (c != 0) {
            c->m = 4;
            n->f36->f8 = *DAT_00568f04[0];
            FUN_001effc0(1, &FUN_00208430, n->f36);
        }
        while (var_s0 != 0) {
            if (((long long)*(const char *)((char *)var_s0 + 70) << 57 >> 57) != 1) {
                var_s0->Set();
            }
            var_s0 = var_s0->f32;
        }
        FUN_00113f78();
    }
}
