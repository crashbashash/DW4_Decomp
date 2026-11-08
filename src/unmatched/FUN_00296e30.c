int FUN_002968c0(void *ply);
void FUN_00295df8(void *ply, int value);
void FUN_00299c20(void *obj, int value);
void FUN_0029a320(const char *message);

extern char DAT_004f3dd8[];

void FUN_00296e30(char *ply, int value) {
    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f3dd8);
        return;
    }
    FUN_00295df8(ply, value);
    FUN_00299c20(ply + 660, value);
}
