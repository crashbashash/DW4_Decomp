typedef struct { char p[9]; unsigned char b0 : 1; unsigned char b1 : 1; unsigned char b2 : 1; unsigned char b3 : 1; unsigned char b4 : 1; unsigned char b5 : 1; unsigned char b6 : 1; unsigned char b7 : 1; unsigned char v; unsigned char c0 : 1; unsigned char c1 : 1; unsigned char c2 : 1; } E;
int FUN_0032d850();
extern int DAT_004fb410[4];
extern void * DAT_0055f5d0[4];
void Gap__igPsx2AudioContext__vfunc_37(int *arg0, void *arg1, int arg2, int arg3) {
    int sp;
    E *p;
    p = (E *)(*(int *)((char *)(DAT_0055f5d0[0]) + 16) + (arg2 * 0x24));
    if (p->b1 != 0) {
        *arg0 = DAT_004fb410[0];
        return;
    }
    if (*(unsigned char *)((char *)arg1 + 8) != 0) {
        FUN_0032d850(&sp, *(int *)((char *)(arg1) + 12), arg2 | 0x260000, arg3, 0, 0);
    } else {
        *(int *)((char *)p + 28) = arg3;
        p->c2 = 1;
    }
    *arg0 = DAT_004fb410[0];
}
