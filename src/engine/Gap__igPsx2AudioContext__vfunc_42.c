typedef struct { char p[9]; unsigned char b0 : 1; unsigned char b1 : 1; unsigned char b2 : 1; unsigned char b3 : 1; unsigned char b4 : 1; unsigned char b5 : 1; unsigned char b6 : 1; unsigned char b7 : 1; unsigned char v : 5; } E;
extern void * DAT_0055f5d0[4];
void Gap__igPsx2AudioContext__vfunc_42(int arg0, int arg1, unsigned char arg2) {
    E *p;
    p = (E *)(*(int *)((char *)(DAT_0055f5d0[0]) + 16) + arg1 * 0x24);
    if ((p->b3 != arg2) && ((p->b1 == 0) || (p->b4 != 0))) {
        p->b3 = arg2;
        p->b4 = 1;
    }
}
