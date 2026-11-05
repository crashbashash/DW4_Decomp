int FUN_001eadf0();
extern unsigned int DAT_00562c70[4];
extern int DAT_0056b058[4];
extern int DAT_0056b0f0[];
extern int DAT_0056b260[];
extern int DAT_0056b2d0[];
extern int DAT_0056b330[];
extern long long DAT_0056b478[4];
extern int DAT_0056b4f8[4];
extern int DAT_0056b530[4];
extern int DAT_0056b550[4];
extern int DAT_0056b568[4];
int FUN_00202e20(int arg0) {
    int temp_a1;
    int temp_a2;
    int var_v0;

    var_v0 = 0;
    if (DAT_0056b058[0] < arg0) {
        return 0;
    }
    temp_a2 = ((unsigned int) DAT_00562c70[0] >> 6) & 1;
    temp_a1 = ((unsigned int) DAT_00562c70[0] >> 0xF) & 3;
    if (arg0 == 1) {
        if (DAT_0056b478[0] & 0x400) {
            return FUN_001eadf0(DAT_0056b0f0[DAT_0056b4f8[0]], temp_a1, temp_a2);
        }
        goto block_6;
    }
block_6:
    if ((arg0 == 1) && (DAT_0056b478[0] & 0x10000)) {
        return FUN_001eadf0(DAT_0056b260[DAT_0056b530[0]], temp_a1, temp_a2);
    }
    if ((temp_a2 != 0) || (temp_a1 != 0)) {
        return FUN_001eadf0(DAT_0056b2d0[DAT_0056b550[0]], temp_a1, temp_a2);
    }
    if (DAT_0056b478[0] & 0x210400) {
        var_v0 = FUN_001eadf0(DAT_0056b330[DAT_0056b568[0]], temp_a1, temp_a2);
    }
    return var_v0;
}
