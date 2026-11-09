struct E { char p[9]; unsigned char bitA : 1; unsigned char bitB : 1; unsigned char bitC : 1; unsigned char bitD : 1; unsigned char bitE : 1; unsigned char bitF : 1; unsigned char bitG : 1; unsigned char bitH : 1; char q[26]; };
struct T { char p[16]; struct E *arr; };
extern struct T * DAT_0055f5d0[4];
void Gap__igPsx2AudioContext__vfunc_57(int arg0, int arg1) {
    DAT_0055f5d0[0]->arr[arg1].bitA = 1;
    DAT_0055f5d0[0]->arr[arg1].bitE = 1;
}
