/* 0x00260d00 — FUN_00260d00 (72 bytes). Validates an index below 256 and a non-null pointer, reporting DAT_004ed900 or DAT_004ed938 through FUN_002607e8 and returning -3 on failure, 0 otherwise. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern char DAT_004ed900[];
extern char DAT_004ed938[];
void FUN_002607e8(const char *message);

int FUN_00260d00(unsigned int index, void *pointer) {
    if (index >= 256) {
        FUN_002607e8(DAT_004ed900);
        return -3;
    }
    if (pointer == 0) {
        FUN_002607e8(DAT_004ed938);
        return -3;
    }
    return 0;
}
