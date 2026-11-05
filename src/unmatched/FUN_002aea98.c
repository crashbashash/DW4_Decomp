/* 0x002aea98 — FUN_002aea98 (72 bytes). Default slot-15 handler: when FUN_002aec58 reports the stream finished, returns position -2 and rate 1 and succeeds with 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002aec58(int obj);

int FUN_002aea98(int obj, int *pos, int *rate) {
    if (FUN_002aec58(obj) == 0) {
        return 0;
    }
    *pos = -2;
    *rate = 1;
    return 0;
}
