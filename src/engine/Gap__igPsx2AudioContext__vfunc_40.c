int FUN_00145960();
int FUN_00145a10();
int FUN_0032d6d0();
typedef struct E {
    char pad0[8];
    unsigned char a0 : 1;
    unsigned char a1 : 1;
    unsigned char a2 : 1;
    unsigned char a3 : 1;
    unsigned char a4 : 1;
    unsigned char a5 : 1;
    unsigned char a6 : 1;
    unsigned char a7 : 1;
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;
    char pad10;
    unsigned char c0 : 1;
    unsigned char c1 : 1;
    unsigned char c2 : 1;
    unsigned char c3 : 1;
    unsigned char c4 : 1;
    unsigned char c5 : 1;
    unsigned char c6 : 1;
    unsigned char c7 : 1;
    int f12;
    char pad16[16];
    int next;
} E;
typedef struct G { char pad[16]; E *arr; } G;
typedef struct A { char pad[8]; unsigned char f8; char pad9[3]; int f12; } A;
extern G *DAT_0055f5d0[4];

void Gap__igPsx2AudioContext__vfunc_40(A *arg0, int arg1) {
    int sp40[5];
    int sp5C; /* matching construct: declaration order — the two status words are declared high slot first so the unit compiler (combat build) assigns sp+0x5c/sp+0x58 as retail does */
    int sp58;
    E *e;
    E *e2;
    int idx;

    e = &DAT_0055f5d0[0]->arr[arg1];
    if (e->a5 == 0 || e->b6 != 0) {
        e->a5 = 1;
        e->b6 = 0 & 1;
        idx = e->next;
        if (idx >= 0) {
            e2 = &DAT_0055f5d0[0]->arr[idx];
            e2->a5 = 1;
            e2->b6 = 0 & 1;
        }
        if (arg0->f8 == 0) {
            e->c3 = 1;
            return;
        }
        sp40[0] = FUN_00145960(arg0, e);
        sp40[1] = e->f12;
        if (e->b4 != 0) {
            sp40[2] = FUN_00145a10(arg0, e);
            FUN_0032d6d0(&sp5C, arg0->f12, arg1 | 0x200000, sp40, 0x10, 0, 0, 0);
            e->b4 = 0 & 1;
            return;
        }
        FUN_0032d6d0(&sp58, arg0->f12, arg1 | 0x2a0000, sp40, 0x10, 0, 0, 0);
    }
}
