/* 0x002b4ba8 — FUN_002b4ba8 (80 bytes). Calls FUN_002b50c8(obj, 16), then tail-calls FUN_002b4c98(obj, arg1, 16, arg2). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b4c98();
int FUN_002b50c8();

void FUN_002b4ba8(int obj, int arg1, int arg2) {
    FUN_002b50c8(obj, 16);
    FUN_002b4c98(obj, arg1, 16, arg2);
}
