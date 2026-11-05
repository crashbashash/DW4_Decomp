/* 0x0029cd58 — FUN_0029cd58 (76 bytes). Reads a coordinate pair from source via FUN_002af540 and stores FUN_002916f8(target, x, y) in *result. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002916f8();
int FUN_002af540();

void FUN_0029cd58(void *source, int *result, int target) {
    int x;
    int y;

    FUN_002af540(source, &x, &y);
    *result = FUN_002916f8(target, x, y);
}
