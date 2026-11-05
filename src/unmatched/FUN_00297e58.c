/* 0x00297e58 — FUN_00297e58 (44 bytes). Resolves the object's handle with FUN_00297810 and passes it with `value` to FUN_002b3bd8. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_00297810(void *obj);
extern void FUN_002b3bd8(int handle, int value);

void FUN_00297e58(void *obj, int value) {
    FUN_002b3bd8(FUN_00297810(obj), value);
}
