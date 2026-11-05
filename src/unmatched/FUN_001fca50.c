extern int DAT_00562c70[4];
extern int DAT_0056b768[4];
extern int DAT_0056b778[4];
void FUN_001fca50(int arg0, int *arg1, int *arg2) {
    if (arg0 > 0) {
        if (((unsigned int) DAT_00562c70[arg0] >> 1) & 1) {
            *arg1 = DAT_0056b768[0] | 0x01080000;
            *arg2 = DAT_0056b778[0] | 0x01080000;
        } else {
            *arg1 = (DAT_0056b768[0] | 0x01000000) & 0xFFF7FFFF;
            *arg2 = (DAT_0056b778[0] | 0x01000000) & 0xFFF7FFFF;
        }
    } else {
        *arg1 = DAT_0056b768[0];
        *arg2 = DAT_0056b778[0];
    }
}
