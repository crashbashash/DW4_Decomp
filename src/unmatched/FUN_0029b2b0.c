/* 0x0029b2b0 — FUN_0029b2b0 (116 bytes). Runs FUN_0026a0a0(a), passes all five arguments to FUN_00269ff0, then calls FUN_0026a300(a, e). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_0026a0a0(int a);
extern void FUN_00269ff0(int a, int b, int c, int d, int e);
extern void FUN_0026a300(int a, int e);

void FUN_0029b2b0(int a, int b, int c, int d, int e) {
    FUN_0026a0a0(a);
    FUN_00269ff0(a, b, c, d, e);
    FUN_0026a300(a, e);
}
