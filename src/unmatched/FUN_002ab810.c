int FUN_002a0bb8();

int FUN_002ab810(void *arg0) {
    if (*(int *)((char *)(arg0) + 4) == 0) {
        return FUN_002a0bb8(0, 0xFF000204);
    }
    if ((unsigned int) *(int *)((char *)(arg0) + 64) < 0x3718U) {
        return FUN_002a0bb8(0, 0xFF000205);
    }
    return 0;
}
