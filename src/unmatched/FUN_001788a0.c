/* 0x001788a0 — FUN_001788a0. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
extern int DAT_005608c0[0x7E];
void FUN_001788a0(void *arg0) {
    int i;
    *(int *)((char *)(arg0) + 1552) = 0;
    i = 0;
    do {
        DAT_005608c0[i] = 0;
    } while (++i < 0x7E);
}
