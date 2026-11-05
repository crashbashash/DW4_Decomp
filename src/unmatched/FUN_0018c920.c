int FUN_0018ab70(void *, int, int *);
int FUN_0018d060(void *, int *);

int FUN_0018c920(void *arg0, void *arg1) {
    int buf[4];

    if (!(*(float *)((char *)(arg1) + 8) <= *(float *)((char *)(arg1) + 20))) {
        return 0;
    }
    FUN_0018ab70(arg1, ~*(int *)((char *)(arg0) + 24) & 7, buf);
    return FUN_0018d060(arg0, buf) == 2;
}
