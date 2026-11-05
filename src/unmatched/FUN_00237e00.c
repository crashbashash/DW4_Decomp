typedef struct S_arg0 { char pad0[8]; int f8; int f12; } S_arg0;
typedef struct S_arg2 { char pad0[12]; int f12; } S_arg2;
int ObjectList_RemoveFirstRetained();

void FUN_00237e00(S_arg0 *arg0, void *arg1, S_arg2 *arg2) {
    int sp3C;
    int sp38;
    int sp34;

    ObjectList_RemoveFirstRetained(&sp3C, arg2->f12, arg1, 0);
    if (*(int *)((char *)(arg2->f12) + 8) == 0) {
        ObjectList_RemoveFirstRetained(&sp38, arg0->f12, arg2, 0);
        ObjectList_RemoveFirstRetained(&sp34, arg0->f8, arg2, 0);
    }
}
