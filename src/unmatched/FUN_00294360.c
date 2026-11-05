/* 0x00294360 — FUN_00294360 (48 bytes). Returns the value FUN_002b23f8 reports for the handle, or -1 when it fails. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002b23f8(int handle, int *out);

int FUN_00294360(int handle) {
    int value;

    if (FUN_002b23f8(handle, &value) != 0) {
        return value;
    }
    return -1;
}
