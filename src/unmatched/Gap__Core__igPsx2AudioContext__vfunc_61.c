struct E {
    char p[8];
    unsigned char a0:1; unsigned char a1:1; unsigned char a2:1; unsigned char a3:1; unsigned char a4:1; unsigned char a5:1; unsigned char a6:1; unsigned char a7:1;
    unsigned char b0:1; unsigned char b1:1; unsigned char b2:1; unsigned char b3:1; unsigned char b4:1; unsigned char b5:1; unsigned char b6:1; unsigned char b7:1;
    char rest[26];
};
struct M { char p[16]; struct E *e; };
extern struct M *DAT_0055f5d0[4];
void Gap__Core__igPsx2AudioContext__vfunc_61(void *arg0, int arg1, int arg2) {
    DAT_0055f5d0[0]->e[arg1].a4 = arg2;
    DAT_0055f5d0[0]->e[arg1].b4 = 1;
}
