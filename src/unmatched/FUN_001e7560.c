extern int DAT_00562c70[4];
extern int DAT_00569330[4];
int FUN_001e7560(int arg0) {
    int idx = DAT_00569330[0];
    int bit = 1 << arg0;
    return (bit & DAT_00562c70[idx]) != 0;
}
