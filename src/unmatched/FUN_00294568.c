/* 0x00294568 — FUN_00294568 (48 bytes). Returns the value FUN_002b2200 reports for the handle, or -1 when it fails. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002b2200(int handle, int *out);

int FUN_00294568(int handle) {
    int value;

    if (FUN_002b2200(handle, &value) != 0) {
        return value;
    }
    return -1;
}
