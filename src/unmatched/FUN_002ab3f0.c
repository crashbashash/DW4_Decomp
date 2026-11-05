/* 0x002ab3f0 — FUN_002ab3f0 (108 bytes). Runs FUN_002ab680 when any of the four checks FUN_002ab460, FUN_002ab4d0, FUN_002ab598 or FUN_002ab5f0 fires. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002ab460(int obj);
int FUN_002ab4d0(int obj);
int FUN_002ab598(int obj);
int FUN_002ab5f0(int obj);
int FUN_002ab680(int obj);

int FUN_002ab3f0(int obj) {
    if (FUN_002ab460(obj) != 0 || FUN_002ab4d0(obj) != 0 || FUN_002ab598(obj) != 0 || FUN_002ab5f0(obj) != 0) {
        return FUN_002ab680(obj);
    }
    return 0;
}
