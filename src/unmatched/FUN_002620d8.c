/* 0x002620d8 — FUN_002620d8 (60 bytes). Rejects a buffer that is not 64-byte aligned (reports DAT_004edd30 through FUN_002607e8, returns -3), otherwise forwards to FUN_00261f48. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern char DAT_004edd30[];
void FUN_002607e8(const char *message);
int FUN_00261f48(int a0, int a1, unsigned int buffer, int size);

int FUN_002620d8(int a0, int a1, unsigned int buffer, int size) {
    if (buffer & 0x3F) {
        FUN_002607e8(DAT_004edd30);
        return -3;
    }
    return FUN_00261f48(a0, a1, buffer, size);
}
