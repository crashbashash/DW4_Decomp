/* 0x00230268 — FUN_00230268 (44 bytes). Packs its four word arguments into a block on the stack and passes the
 * block to FUN_00230150. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_00230150(int *args);

void FUN_00230268(int a, int b, int c, int d) {
    int args[4];

    args[0] = a;
    args[1] = b;
    args[2] = c;
    args[3] = d;
    FUN_00230150(args);
}
