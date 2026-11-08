typedef struct {
    char pad0[20];
    int f20;
    int f24;
} Sub2a0960;

int FUN_002a0960(char *obj) {
    Sub2a0960 *sub = (Sub2a0960 *)(obj + 212);

    if (*(int *)(obj + 120) == 0) {
        return -1;
    }
    if (sub->f20 == 0) {
        return -1;
    }
    return sub->f24;
}
