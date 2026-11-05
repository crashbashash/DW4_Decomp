/* 0x0026ae18 — FUN_0026ae18 (100 bytes). Calls FUN_00275200 with fields 8, 12, 16 and 4 of a descriptor and FUN_00275220 with field 0, or both with zeros for a null descriptor. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* Five-word descriptor read by FUN_0026ad50, FUN_0026adb0 and FUN_0026ae18. */
typedef struct Desc_26ad50 {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
} Desc_26ad50;
void FUN_00275200(int a0, int a1, int a2, int a3);
void FUN_00275220(int a0);

void FUN_0026ae18(Desc_26ad50 *desc) {
    if (desc != 0) {
        FUN_00275200(desc->f8, desc->f12, desc->f16, desc->f4);
        FUN_00275220(desc->f0);
        return;
    }
    FUN_00275200(0, 0, 0, 0);
    FUN_00275220(0);
}
