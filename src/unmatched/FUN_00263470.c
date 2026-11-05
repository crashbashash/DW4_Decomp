/* 0x00263470 — FUN_00263470 (216 bytes). Drops the counter DAT_0049c8d8 and, when it reaches zero, runs a fixed sequence of FUN_0026b900 … FUN_0025f2e8 calls with DAT_004a9b1c cleared, setting it back to 1 afterwards. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int DAT_0049c8d8;
extern int DAT_0049c8e0;
extern int DAT_0049c8ec;
extern int DAT_004a9b1c;
void FUN_0026b900(void);
void FUN_00265c18(void);
void FUN_00260b30(void);
void FUN_00269c98(void);
void FUN_00277918(void);
void FUN_0025f2d0(void);
void FUN_0027e6d0(int key, int value);
void FUN_0027ec50(void);
void FUN_00265f88(void);
void FUN_00260788(void);
void FUN_0027b390(void);
void FUN_0027bcd0(void);
void FUN_0027c810(void);
void FUN_0025f2e8(void);

void FUN_00263470(void) {
    if (--DAT_0049c8d8 == 0) {
        DAT_004a9b1c = 0;
        FUN_0026b900();
        FUN_00265c18();
        FUN_00260b30();
        FUN_00269c98();
        FUN_00277918();
        FUN_0025f2d0();
        FUN_0027e6d0(2, 1);
        FUN_0027e6d0(4, DAT_0049c8ec);
        FUN_0027e6d0(5, DAT_0049c8e0);
        FUN_0027ec50();
        FUN_00265f88();
        FUN_00260788();
        FUN_0027b390();
        FUN_0027bcd0();
        FUN_0027c810();
        FUN_0025f2e8();
        DAT_004a9b1c = 1;
    }
}
