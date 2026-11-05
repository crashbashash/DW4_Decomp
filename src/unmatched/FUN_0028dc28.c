/* 0x0028dc28 — FUN_0028dc28 (80 bytes). Runs FUN_0028da60 on the object; on failure reports error 0xFF020103 through FUN_0028d890, otherwise sets its first word to 1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_0028da60(int *obj);
extern int FUN_0028d890(int zero, int code);

int FUN_0028dc28(int *obj) {
    if (FUN_0028da60(obj) != 0) {
        return FUN_0028d890(0, 0xFF020103);
    }
    *obj = 1;
    return 0;
}
