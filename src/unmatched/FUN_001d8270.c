int FUN_001d81e0();
extern int DAT_0055f060[4];
extern int DAT_0055f088[4];
int FUN_001d8270(int arg0) {
    if (arg0 == DAT_0055f088[0]) {
        return 1;
    }
    if (arg0 == DAT_0055f060[0]) {
        return FUN_001d81e0();
    }
    return 0;
}
