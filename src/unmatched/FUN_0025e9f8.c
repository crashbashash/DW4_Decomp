/* Compares four bytes at a pointer with the tag at DAT_004ed850; returns 1 when they are equal. */
int FUN_00127004(const void *a, const void *b, int length);
extern char DAT_004ed850[];

int FUN_0025e9f8(const void *data) {
    return FUN_00127004(data, DAT_004ed850, 4) == 0;
}
