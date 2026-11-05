/* 0x0026ad50 — FUN_0026ad50 (92 bytes). Calls FUN_00274f10 with fields 0, 8, 12 and 4 of a descriptor and returns its result; for a null descriptor calls it with zeros and returns 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* Five-word descriptor read by FUN_0026ad50, FUN_0026adb0 and FUN_0026ae18. */
typedef struct Desc_26ad50 {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
} Desc_26ad50;
int FUN_00274f10(int a0, int a1, int a2, int a3);

int FUN_0026ad50(Desc_26ad50 *desc) {
    int result = 0;

    if (desc != 0) {
        result = FUN_00274f10(desc->f0, desc->f8, desc->f12, desc->f4);
    } else {
        FUN_00274f10(0, 0, 0, 0);
    }
    return result;
}
