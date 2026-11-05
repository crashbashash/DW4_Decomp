struct R { int v; R(int x) { v = x; } R() {} };
struct E {
    char p[11];
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;
    int w12;
    float g16;
    float g20;
    char tail[12];
};
struct Tbl { char p[16]; E *arr; };
extern "C" {
int FUN_00145960(...);
R FUN_0032d850(...);
extern int DAT_004fb410[4];
extern Tbl *DAT_0055f5d0[4];
R Gap__Core__igPsx2AudioContext__vfunc_35(char *arg1, int arg2, float fparg0);
}
R Gap__Core__igPsx2AudioContext__vfunc_35(char *arg1, int arg2, float fparg0) {
    E *e;
    int s2;

    e = DAT_0055f5d0[0]->arr + arg2;
    if (fparg0 == 0.0f) {
        e->g16 = 1.0f;
        e->g20 = 1.0f;
    } else if (fparg0 < 0.0f) {
        e->g16 = 1.0f;
        e->g20 = 1.0f + fparg0;
    } else {
        e->g20 = 1.0f;
        e->g16 = 1.0f - fparg0;
    }
    if (*(unsigned char *)(arg1 + 8) != 0) {
        s2 = *(int *)(arg1 + 12);
        FUN_0032d850(s2, arg2 | 0x270000, FUN_00145960(arg1, e), 0, 0);
    } else {
        e->b0 = 1;
    }
    return R(DAT_004fb410[0]);
}
