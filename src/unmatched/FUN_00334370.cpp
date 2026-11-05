extern "C" {
/* 0x00334370 — FUN_00334370. hand-matched; verified byte-identical by tools/verify.py. */
int FUN_00262540(int);

int FUN_00334370(void *arg0) {
    if (*(unsigned char *)((char *)(arg0) + 44) != 0) {
        return (FUN_00262540(*(int *)((char *)(arg0) + 96)) << 0xB) + 0x800;
    }
    return 0;
}
}
