/* 0x00296290 — FUN_00296290 (56 bytes). Stores FUN_001033c0(FUN_00102df0(), 1, 30) into *out; the first argument is unused. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_00102df0(void);
extern int FUN_001033c0(int handle, int a, int b);

void FUN_00296290(void *unused, int *out) {
    *out = FUN_001033c0(FUN_00102df0(), 1, 30);
}
