typedef struct { char p[9]; unsigned char b0 : 1; unsigned char b1 : 1; unsigned char b2 : 1; unsigned char b3 : 1; unsigned char b4 : 1; unsigned char b5 : 1; unsigned char b6 : 1; unsigned char b7 : 1; unsigned char v : 5; } E;
extern void * DAT_0055f5d0[4];
void Gap__Core__igPsx2AudioContext__vfunc_60(int arg0, int arg1, int arg2, int arg3) {
    int temp_v1;

    temp_v1 = arg1 * 0x24;
    ((E *)(*(int *)((char *)(DAT_0055f5d0[0]) + 16) + temp_v1))->b2 = arg2;
    ((E *)(*(int *)((char *)(DAT_0055f5d0[0]) + 16) + temp_v1))->v = arg3;
    ((E *)(*(int *)((char *)(DAT_0055f5d0[0]) + 16) + temp_v1))->b5 = 1;
    ((E *)(*(int *)((char *)(DAT_0055f5d0[0]) + 16) + temp_v1))->b4 = 1;
}
