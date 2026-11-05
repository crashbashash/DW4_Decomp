int FUN_00145a10();
int FUN_0032d850();

typedef struct E {
    char pad0[9];
    unsigned char a9 : 4;
    unsigned char f9 : 1;
    unsigned char c9 : 3;
    char pad10;
    unsigned char a11 : 4;
    unsigned char f11 : 1;
    unsigned char c11 : 3;
    char pad12[24];
} E;
typedef struct G { char pad[16]; E *arr; } G;
typedef struct A { char pad[8]; unsigned char f8; char pad9[3]; int f12; } A;
extern G *DAT_0055f5d0[4];

void Gap__Core__igPsx2AudioContext__vfunc_41(A *arg0, int arg1) {
    int sp4C;
    int temp_s2;
    E *temp_s0;

    temp_s0 = &DAT_0055f5d0[0]->arr[arg1];
    if (arg0->f8 == 0) {
        temp_s0->f11 = 1;
        return;
    }
    temp_s2 = arg0->f12;
    FUN_0032d850(&sp4C, temp_s2, arg1 | 0xD0000, FUN_00145a10(arg0, temp_s0), 0, 1);
    temp_s0->f9 = 0 & 1;
}
