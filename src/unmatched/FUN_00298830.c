/* 0x00298830 — FUN_00298830 (80 bytes). Passes two values and a flag (`mode` == 1) to FUN_002b3dd0 on the object's handle from FUN_00297810. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_00297810(void *obj);
extern void FUN_002b3dd0(int handle, int a, int b, int flag);

void FUN_00298830(void *obj, int a, int b, int mode) {
    FUN_002b3dd0(FUN_00297810(obj), a, b, mode == 1);
}
