int FUN_0018ab70();
int FUN_0018d060();

int FUN_0018b110(void *arg0, void *arg1) {
    int sp20[4];

    if (!(*(float *)((char *)(arg0) + 8) <= *(float *)((char *)(arg0) + 20))) {
        return 0;
    }
    FUN_0018ab70(arg0, ~*(int *)((char *)(arg1) + 24) & 7, sp20);
    return FUN_0018d060(arg1, sp20) == 2;
}
