/* 0x00281018 — FUN_00281018 (96 bytes). If the context is open, runs FUN_00281078(arg, extra) then repeats FUN_00281df0/FUN_00281cf8 on `arg` while the latter returns 1; a final 2 maps to 0, a closed context to -30. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_00281078();
int FUN_00281df0();
int FUN_00281cf8();

struct Ctx00281018 {
    char pad0[2740];
    int open; /* +2740 */
};

extern struct Ctx00281018 *DAT_004bb114;

int FUN_00281018(int arg, int extra) {
    int status;

    if (DAT_004bb114->open == 0) {
        return -30;
    }
    FUN_00281078(arg, extra);
    do {
        FUN_00281df0(arg);
        status = FUN_00281cf8(arg);
    } while (status == 1);
    if (status == 2) {
        status = 0;
    }
    return status;
}
