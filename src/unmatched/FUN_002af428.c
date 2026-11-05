/* 0x002af428 — FUN_002af428 (96 bytes). For event kind 2, reads the elapsed position/rate (FUN_002af540) and advances both clocks by it (FUN_002af488, FUN_002af4f0). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_002af540(int obj, int *pos, int *rate);
void FUN_002af488(int obj, int pos, int rate);
void FUN_002af4f0(int obj, int pos, int rate);

void FUN_002af428(int obj, unsigned int kind) {
    int pos;
    int rate;

    switch (kind) {
    case 0:
    case 1:
        break;
    case 2:
        FUN_002af540(obj, &pos, &rate);
        FUN_002af488(obj, pos, rate);
        FUN_002af4f0(obj, pos, rate);
        break;
    }
}
