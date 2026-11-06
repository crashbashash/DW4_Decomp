int FUN_0032d9b0();

typedef struct E {
    char pad0[8];
    unsigned char a8 : 5;
    unsigned char f8 : 1;
    unsigned char c8 : 2;
    char pad9[2];
    unsigned char a11 : 3;
    unsigned char f11 : 1;
    unsigned char c11 : 4;
    char pad12[20];
    int next;
} E;
typedef struct G { char pad[16]; E *arr; } G;
typedef struct A { char pad[8]; unsigned char f8; char pad9[3]; int f12; } A;
extern G *DAT_0055f5d0[4];

void Gap__igPsx2AudioContext__vfunc_43(A *arg0, int arg1) {
    int sp1C;
    E *e;
    E *e2;
    int idx;

    e = &DAT_0055f5d0[0]->arr[arg1];
    e->f8 = 0 & 1;
    idx = e->next;
    if (idx >= 0) {
        e2 = &DAT_0055f5d0[0]->arr[idx];
        e2->f8 = 0 & 1;
    }
    if (arg0->f8 != 0) {
        FUN_0032d9b0(&sp1C, arg0->f12, arg1 | 0x210000, 0);
        return;
    }
    e->f11 = 1;
}
