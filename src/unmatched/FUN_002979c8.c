/* 0x002979c8 — 12 bytes. Copies word +0x30 of arg0 into +0x4c of arg1, returning it (v0). */
int FUN_002979c8(void *arg0, void *arg1) {
    return *(int *)((char *)(arg1) + 76) = *(int *)((char *)(arg0) + 48);
}
