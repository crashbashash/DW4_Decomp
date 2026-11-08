int FUN_00298250(void *ply);
int FUN_002b0ff8(int stream, int index, int a, int b);

int FUN_002986c0(char *ply) {
    if (FUN_00298250(ply) == 1) {
        return 0;
    }
    if (*(int *)(ply + 400) == 0) {
        return 0;
    }
    if (FUN_002b0ff8(*(int *)(ply + 64), 2, 0, 0) != 0) {
        return -1;
    }
    return 0;
}
