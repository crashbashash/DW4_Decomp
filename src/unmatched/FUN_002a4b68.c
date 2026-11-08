int FUN_002a4bb0(int);

int FUN_002a4b68(int a0, int level, int kind) {
    if (kind == 128) {
        return 1;
    }
    if (level < 5 && FUN_002a4bb0(a0) == 1) {
        return 1;
    }
    return 0;
}
