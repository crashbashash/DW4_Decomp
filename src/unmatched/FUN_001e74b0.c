int FUN_001e7930();
extern int DAT_00562c70[0x100];
extern int DAT_00569330[4];
void FUN_001e74b0(int arg0) {
    int temp_a4 = 1 << arg0;
    int *temp_a3 = &DAT_00562c70[DAT_00569330[0]];
    int temp_a2 = *temp_a3;
    if (!(temp_a4 & temp_a2)) {
        *temp_a3 = temp_a2 | temp_a4;
        FUN_001e7930(arg0, 1);
    }
}
