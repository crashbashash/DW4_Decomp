struct E { char p[9]; unsigned char b0 : 1; unsigned char b1 : 1; unsigned char b2 : 1; unsigned char b3 : 1; unsigned char b4 : 1; unsigned char b5 : 1; unsigned char b6 : 1; unsigned char b7 : 1; char q[26]; };
struct T { char p[16]; struct E *arr; };
extern struct T * DAT_0055f5d0[4];
void Gap__Core__igPsx2AudioContext__vfunc_58(int arg0, int arg1) {
    DAT_0055f5d0[0]->arr[arg1].b1 = 1;
    DAT_0055f5d0[0]->arr[arg1].b4 = 1;
}
