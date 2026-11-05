/* 0x0032bc80 - FUN_0032bc80. typed struct, unsigned char element read, alternate compiler -O3 Verified byte-identical by tools/verify.py. */
typedef struct S0 { char pad24[24]; int f24; char pad28[16]; unsigned char *f44; char pad48[4]; int f52; int f56; int f60; } S0;
int FUN_0010f970();

int FUN_0032bc80(S0 *arg0) {
    int sp1C;
    int i;

    if (arg0->f60 != 0) {
        FUN_0010f970(arg0->f24, &sp1C, 1);
        return sp1C;
    }
    i = arg0->f52;
    if (i >= arg0->f56) {
        return -1;
    }
    arg0->f52 = i + 1;
    return arg0->f44[arg0->f52 - 1];
}
