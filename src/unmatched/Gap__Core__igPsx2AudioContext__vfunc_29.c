int FUN_0032d9b0();
typedef struct { char p[8]; unsigned char b0 : 1; } B;
extern int DAT_004fb410[4];
extern void * DAT_0055f5d0[4];
void Gap__Core__igPsx2AudioContext__vfunc_29(int *arg0, void *arg1, int arg2) {
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    void *temp_s0;
    int temp_a3;
    int temp_a0;
    int sp3C;

    temp_a0 = *(int *)((char *)(DAT_0055f5d0[0]) + 16);
    temp_s0 = (void *)(temp_a0 + (arg2 * 0x24));
    temp_a3 = *(int *)((char *)(temp_s0) + 32);
    if (temp_a3 >= 0) {
        *(int *)((char *)((temp_a0 + (temp_a3 * 0x24))) + 32) = -1;
    }
    FUN_0032d9b0(&sp3C, *(int *)((char *)(arg1) + 12), arg2 | 0x90000, 0);
    ((B *)temp_s0)->b0 = 0;
    *arg0 = DAT_004fb410[0];
}
