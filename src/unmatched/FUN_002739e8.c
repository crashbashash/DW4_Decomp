/* 0x002739e8 — FUN_002739e8 (88 bytes). Calls FUN_00116740(a, b, word 0x004aa74c) between FUN_002725a0(0x8000)
   and FUN_002725a0(0x8001) and returns its result. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_002725a0(int value);
extern int FUN_00116740(int a, int b, int c);
extern int DAT_004aa74c;

int FUN_002739e8(int a, int b) {
    int result;

    FUN_002725a0(0x8000);
    result = FUN_00116740(a, b, DAT_004aa74c);
    FUN_002725a0(0x8001);
    return result;
}
