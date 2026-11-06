typedef struct { char p[11]; unsigned char f:1; } B11;
int FUN_00145960();
int FUN_0032d850();
extern int DAT_004fb410[4];
extern void * DAT_0055f5d0[4];
void Gap__igPsx2AudioContext__vfunc_34(int *arg0, void *arg1, int arg2, float fparg0) {
    int sp4C;
    int temp_s2;
    void *temp_a2;
    void *g;

    g = DAT_0055f5d0[0];
    temp_a2 = (void *)(*(int *)((char *)(g) + 16) + (arg2 * 0x24));
    *(float *)((char *)(temp_a2) + 24) = fparg0;
    if (*(unsigned char *)((char *)(arg1) + 8) != 0) {
        temp_s2 = *(int *)((char *)(arg1) + 12);
        FUN_0032d850(&sp4C, temp_s2, arg2 | 0x270000, FUN_00145960(arg1, temp_a2, temp_a2, g), 0, 0);
    } else {
        ((B11 *)temp_a2)->f = 1;
    }
    *arg0 = DAT_004fb410[0];
}
